(defpackage :gpp-interpreter
  (:use :common-lisp)
  (:export :gppinterpreter))

(in-package :gpp-interpreter)

(defstruct fraction
  (numerator 0 :type integer)
  (denominator 1 :type integer))

(defstruct parse-tree
  type                  ; Node tipi (expression, function, etc.)
  value                 ; Node değeri
  children)             ; Alt parse tree'leri

;; Earley Parsing Veri Yapısı
(defstruct earley-item
  rule                  ; Dilbilgisi kuralı
  dot-position          ; İşaretçi konumu
  start-index           ; Başlangıç indeksi
  end-index             ; Bitiş indeksi
  parse-tree)           ; İlişkili parse tree'si

;; G++ Dilbilgisi Kuralları
(defparameter *grammar-rules*
  '((:start → :input)
    (:input → :expression)
    (:input → :expression-list)
    
    (:expression → :number)
    (:expression → :arithmetic-expression)
    (:expression → :boolean-expression)
    (:expression → :conditional-expression)
    (:expression → :identifier)
    
    (:arithmetic-expression → (+ :expression :expression))
    (:arithmetic-expression → (- :expression :expression))
    (:arithmetic-expression → (* :expression :expression))
    (:arithmetic-expression → (/ :expression :expression))
    
    (:boolean-expression → (and :expression :expression))
    (:boolean-expression → (or :expression :expression))
    (:boolean-expression → (not :expression))
    
    (:conditional-expression → (if :expression :expression :expression))
    
    (:number → :fraction)
    (:fraction → :integer)
    (:fraction → (:integer ":" :integer))))

(defun tokenize (input)
  (let ((tokens '())
        (current-token "")
        (in-comment nil))
    (loop for char across input
          do (cond
              ((and (char= char #\;) (not in-comment))
               (if (string= current-token "")
                   (setf in-comment t)
                   (progn
                     (when (not (string= current-token ""))
                       (push current-token tokens))
                     (setf current-token "")
                     (setf in-comment t))))
              
              (in-comment
               (when (char= char #\Newline)
                 (setf in-comment nil)))
              
              ((or (char= char #\Space) (char= char #\Tab) (char= char #\Newline))
               (when (not (string= current-token ""))
                 (push current-token tokens)
                 (setf current-token "")))
              
              ((find (string char) '("+" "-" "/" "*" "(" ")" ",") :test #'string=)
               (when (not (string= current-token ""))
                 (push current-token tokens))
               (push (string char) tokens)
               (setf current-token ""))
              
              (t (setf current-token (concatenate 'string current-token (string char))))))
    
    (when (not (string= current-token ""))
      (push current-token tokens))
    
    (nreverse tokens)))

;; Earley Parsing Algoritması
(defun earley-parse (tokens grammar)
  (let* ((n (length tokens))
         (chart (make-array (1+ n) :initial-element nil))
         (start-rule (find :start grammar :key #'first)))
    
    ;; Başlangıç durumunu ekle
    (push (make-earley-item 
           :rule start-rule
           :dot-position 0
           :start-index 0
           :end-index 0
           :parse-tree (make-parse-tree 
                        :type :start 
                        :value nil 
                        :children nil))
          (aref chart 0))
    
    ;; Her chart indeksi için parsing
    (loop for i from 0 below (1+ n)
          do (process-chart-entry chart tokens grammar i))
    
    ;; Son chart'ta geçerli bir parse var mı?
    (find-valid-parse chart n)))

(defun process-chart-entry (chart tokens grammar chart-index)
  (let ((current-items (aref chart chart-index)))
    (loop 
      (let ((initial-item-count (length current-items)))
        (dolist (item current-items)
          (cond
            ;; Item tamamlandıysa
            ((item-completed-p item)
             (complete-item chart item chart-index))
            
            ;; Henüz tamamlanmamışsa
            (t
             (let ((next-symbol (next-expected-symbol item)))
               (cond
                 ;; Terminal sembol
                 ((and (stringp next-symbol)
                       (< chart-index (length tokens))
                       (string= next-symbol (nth chart-index tokens)))
                  (predict-terminal chart item tokens chart-index))
                 
                 ;; Non-terminal sembol
                 ((symbolp next-symbol)
                  (predict-non-terminal chart grammar item next-symbol chart-index)))))))
        
        ;; Yeni item eklenmediyse parsing'i bitir
        (when (= initial-item-count (length (aref chart chart-index)))
          (return))))))

(defun item-completed-p (item)
  (= (earley-item-dot-position item)
     (length (rest (earley-item-rule item)))))

(defun next-expected-symbol (item)
  (nth (earley-item-dot-position item) 
       (rest (earley-item-rule item))))

(defun predict-terminal (chart item tokens chart-index)
  (let ((new-item (copy-earley-item item)))
    (incf (earley-item-dot-position new-item))
    (setf (earley-item-end-index new-item) (1+ chart-index))
    (push new-item (aref chart (1+ chart-index)))))

(defun predict-non-terminal (chart grammar item symbol chart-index)
  (let ((matching-rules 
         (remove-if-not 
          (lambda (rule) (eq (first rule) symbol)) 
          grammar)))
    (dolist (rule matching-rules)
      (push (make-earley-item 
             :rule rule
             :dot-position 0
             :start-index chart-index
             :end-index chart-index
             :parse-tree (make-parse-tree 
                          :type symbol 
                          :value nil 
                          :children nil))
            (aref chart chart-index)))))

(defun complete-item (chart item chart-index)
  (let ((completed-symbol (first (earley-item-rule item))))
    (dolist (prev-item (aref chart (earley-item-start-index item)))
      (when (and (not (item-completed-p prev-item))
                 (eq (next-expected-symbol prev-item) completed-symbol))
        (let ((new-item (copy-earley-item prev-item)))
          (incf (earley-item-dot-position new-item))
          (setf (earley-item-end-index new-item) chart-index)
          (push new-item (aref chart chart-index)))))))

(defun find-valid-parse (chart n)
  (let ((final-items 
         (remove-if-not 
          (lambda (item) 
            (and (eq (first (earley-item-rule item)) :start)
                 (item-completed-p item)
                 (= (earley-item-end-index item) n)))
          (aref chart n))))
    (and final-items t)))

(defun parse-and-evaluate (input)
  (let* ((tokens (tokenize input))
         (parse-valid (earley-parse tokens *grammar-rules*))
         (env (make-hash-table)))
    (when parse-valid
      (evaluate-expression 
       (parse-expression tokens) 
       env))))

(defun gppinterpreter (&optional filename)
  (let ((env (make-hash-table))
        (*read-eval* nil))
    (when filename
      (format t "$ g++ ~A~%" filename)
      (with-open-file (file filename)
        (loop for line = (read-line file nil)
              while line
              do (process-line line env))))
    
    (format t "> ")
    (force-output)
    (loop for line = (read-line *standard-input* nil nil)
          while line
          do (process-line line env)
             (format t "> ")
             (force-output))))

(defun process-line (line env)
  (handler-case
      (let* ((tokens (tokenize line))
             (expr (parse-expression tokens))
             (result (when expr (evaluate-expression expr env))))
        (when result
          (let ((numerator (fraction-numerator result))
                (denominator (fraction-denominator result)))
            (format t "~A~%" 
                    (if (= denominator 1)
                        numerator 
                        (format nil "~A/~A" numerator denominator))))))
    (error (e)
      (format t "ERROR: ~A~%" e))))

(defun parse-expression (tokens)
  (if (null tokens)
      nil
      (let ((first-token (first tokens)))
        (cond
          ((string= first-token "(")
           (multiple-value-bind (expr remaining)
               (parse-list (rest tokens))
             (values expr remaining)))
          
          ((every #'digit-char-p first-token)
           (values (parse-fraction first-token) (rest tokens)))
          
          (t (values (intern (string-upcase first-token))
                    (rest tokens)))))))

(defun parse-fraction (token)
  "Parse a fraction from string (e.g., '3:4' or '5')"
  (let ((parts (split-string token)))
    (make-fraction 
     :numerator (parse-integer (first parts))
     :denominator (if (second parts)
                      (parse-integer (second parts))
                      1))))

(defun split-string (string &key (delimiter #\:))
  "Split a string by delimiter"
  (loop with len = (length string)
        for start = 0 then (1+ pos)
        for pos = (position delimiter string :start start)
        collect (subseq string start (or pos len))
        while pos))

(defun parse-list (tokens)
  (let ((result '())
        (current tokens))
    (loop
      (when (null current)
        (error "Unexpected end of input"))
      (let ((token (first current)))
        (cond
          ((string= token ")")
           (return (values (nreverse result) (rest current))))
          (t (multiple-value-bind (expr remaining)
                 (parse-expression current)
               (push expr result)
               (setf current remaining))))))))

(defun evaluate-expression (expr env)
  "Evaluate a G++ expression"
  (cond
    ;; Handle fraction structs directly
    ((fraction-p expr) expr)
    
    ;; Numbers
    ((numberp expr)
     (make-fraction :numerator expr :denominator 1))
    
    ;; Lists (function calls and special forms)
    ((listp expr)
     (let ((operator (first expr))
           (args (rest expr)))
       (case operator
         (+ (evaluate-plus (evaluate-expression (first args) env)
                          (evaluate-expression (second args) env)))
         (- (evaluate-minus (evaluate-expression (first args) env)
                          (evaluate-expression (second args) env)))
         (* (evaluate-mult (evaluate-expression (first args) env)
                         (evaluate-expression (second args) env)))
         (/ (evaluate-div (evaluate-expression (first args) env)
                        (evaluate-expression (second args) env)))
         (and (evaluate-and (evaluate-expression (first args) env)
                          (evaluate-expression (second args) env)))
         (or (evaluate-or (evaluate-expression (first args) env)
                         (evaluate-expression (second args) env)))
         (not (evaluate-not (evaluate-expression (first args) env)))
         (if (evaluate-if args env))
         (exit (progn (format t "Goodbye!~%") (sb-ext:quit)))
         (equal (evaluate-equal (evaluate-expression (first args) env)
                              (evaluate-expression (second args) env)))
         (less (evaluate-less (evaluate-expression (first args) env)
                            (evaluate-expression (second args) env)))
         (for (evaluate-for args env))
         (while (evaluate-while args env))
         (set (evaluate-set (first args) (second args) env))
         (t (error "Unknown operator: ~A" operator)))))
    
    ;; Boolean constants
    ((eq expr 'true) (make-fraction :numerator 1 :denominator 1))
    ((eq expr 'false) (make-fraction :numerator 0 :denominator 1))
    ((eq expr 'nil) (make-fraction :numerator 0 :denominator 1))
    
    ;; Variables
    ((symbolp expr)
     (let ((value (gethash expr env)))
       (if value
           value
           (error "Undefined variable: ~A" expr))))
    
    (t (error "Invalid expression: ~A" expr))))

;; Arithmetic operations
(defun evaluate-plus (f1 f2)
  (make-fraction 
   :numerator (+ (* (fraction-numerator f1) (fraction-denominator f2))
                 (* (fraction-numerator f2) (fraction-denominator f1)))
   :denominator (* (fraction-denominator f1) (fraction-denominator f2))))

(defun evaluate-minus (f1 f2)
  (make-fraction 
   :numerator (- (* (fraction-numerator f1) (fraction-denominator f2))
                 (* (fraction-numerator f2) (fraction-denominator f1)))
   :denominator (* (fraction-denominator f1) (fraction-denominator f2))))

(defun evaluate-mult (f1 f2)
  (make-fraction 
   :numerator (* (fraction-numerator f1) (fraction-numerator f2))
   :denominator (* (fraction-denominator f1) (fraction-denominator f2))))

(defun evaluate-div (f1 f2)
  (if (zerop (fraction-numerator f2))
      (error "Division by zero")
      (make-fraction 
       :numerator (* (fraction-numerator f1) (fraction-denominator f2))
       :denominator (* (fraction-denominator f1) (fraction-numerator f2)))))

;; Logical operations
(defun evaluate-and (f1 f2)
  (make-fraction 
   :numerator (if (and (not (zerop (fraction-numerator f1)))
                      (not (zerop (fraction-numerator f2))))
                 1
                 0)
   :denominator 1))

(defun evaluate-or (f1 f2)
  (make-fraction 
   :numerator (if (or (not (zerop (fraction-numerator f1)))
                     (not (zerop (fraction-numerator f2))))
                 1
                 0)
   :denominator 1))

(defun evaluate-not (f)
  (make-fraction 
   :numerator (if (zerop (fraction-numerator f)) 1 0)
   :denominator 1))

(defun evaluate-if (args env)
  (let ((condition (evaluate-expression (first args) env)))
    (if (not (zerop (fraction-numerator condition)))
        (evaluate-expression (second args) env)
        (evaluate-expression (third args) env))))

;; Variable operations
(defun evaluate-set (var expr env)
  (let ((value (evaluate-expression expr env)))
    (setf (gethash var env) value)
    value))

;; Comparison operations
(defun evaluate-equal (f1 f2)
  (make-fraction 
   :numerator (if (and (= (fraction-numerator f1) (fraction-numerator f2))
                      (= (fraction-denominator f1) (fraction-denominator f2)))
                 1 0)
   :denominator 1))

(defun evaluate-less (f1 f2)
  (let ((v1 (/ (fraction-numerator f1) (fraction-denominator f1)))
        (v2 (/ (fraction-numerator f2) (fraction-denominator f2))))
    (make-fraction 
     :numerator (if (< v1 v2) 1 0)
     :denominator 1)))

;; Loop operations
(defun evaluate-for (args env)
  "Evaluate a for loop expression: (for (var start end) body)"
  (let* ((loop-spec (first args))
         (var (first loop-spec))
         (start (evaluate-expression (second loop-spec) env))
         (end (evaluate-expression (third loop-spec) env))
         (body (second args))
         (result (make-fraction :numerator 0 :denominator 1)))
    
    (loop for i from (fraction-numerator start) to (fraction-numerator end)
          do (progn
               (setf (gethash var env) (make-fraction :numerator i :denominator 1))
               (setf result (evaluate-expression body env))))
    result))

(defun evaluate-while (args env)
  "Evaluate a while loop expression: (while condition body)"
  (let ((condition (first args))
        (body (second args))
        (result (make-fraction :numerator 0 :denominator 1)))
    
    (loop while (not (zerop (fraction-numerator (evaluate-expression condition env))))
          do (setf result (evaluate-expression body env)))
    result))

(defun main ()
  (gppinterpreter "input.g++"))

(main)