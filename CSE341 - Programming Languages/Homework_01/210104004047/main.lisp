;; Load Quicklisp if not already loaded
(let ((quicklisp-file "~/quicklisp/setup.lisp"))
  (when (not (probe-file quicklisp-file))
    (error "Quicklisp not found. Please install Quicklisp."))
  (load quicklisp-file))

;; Load the cl-ppcre library
(ql:quickload "cl-ppcre")

(defun line-type (line)
  "Identify the type of a line in C code."
  (cond
    ((cl-ppcre:scan "if\\s*\\(.*\\)\\s*{" line) 'if-statement)
    ((cl-ppcre:scan "for\\s*\\(.*\\)\\s*{" line) 'for-loop)
    ((cl-ppcre:scan "while\\s*\\(.*\\)\\s*{" line) 'while-loop)
    ((cl-ppcre:scan "\\breturn\\b" line) 'return-value)
    ((cl-ppcre:scan "\\b\\w+\\s*=\\s*\\w+\\s*\\(.*\\)\\s*;" line) 'variable-by-function)
    ((cl-ppcre:scan "\\b\\w+\\s*=\\s*[^;]*;" line) 'variable-assignment)
    ((cl-ppcre:scan "\\b\\w+\\s+\\w+\\s*;" line) 'variable-declaration)
    ((cl-ppcre:scan "\\b\\w+\\s+\\w+\\s*=\\s*[^;]*;" line) 'variable-declaration-assignment)
    ((cl-ppcre:scan "\\w+\\s+\\w+\\s*\\(.*\\)\\s*;" line) 'function-declaration)
    ((cl-ppcre:scan "\\w+\\s+\\w+\\s*\\(.*\\)\\s*{" line) 'function-definition)
    ((cl-ppcre:scan "printf\\s*\\(\"\.*\",\\s*\.*\\s*\\);" line) 'print-function-variable)
    ((cl-ppcre:scan "printf\\s*\\(\"\.*\"\\s*\\);" line) 'print-function-literal)
    ((cl-ppcre:scan "\\s*}\\s*" line) 'close-brace)
    ((cl-ppcre:scan "^\\s*$" line) 'empty-line)
    (t 'unknown))
)

(defun conversion-foo (line-type)
  "Select the appropriate conversion function based on the line type."
  (cond
    ((eq line-type 'if-statement) #'convert-if-statement)
    ((eq line-type 'for-loop) #'convert-for-loop)
    ((eq line-type 'while-loop) #'convert-while-loop)
    ((eq line-type 'operation) #'convert-logical-arithmetic-operation)
    ((eq line-type 'function-declaration) #'convert-function-declaration)
    ((eq line-type 'function-definition) #'convert-function-definition)
    ((eq line-type 'variable-by-function) #'convert-variable-by-function)
    ((eq line-type 'variable-declaration) #'convert-variable-declaration)
    ((eq line-type 'variable-assignment) #'convert-variable-assignment)
    ((eq line-type 'print-function-variable) #'convert-print-function-variable)
    ((eq line-type 'print-function-literal) #'convert-print-function-literal)
    ((eq line-type 'return-value) #'convert-return-value)
    ((eq line-type 'close-brace) #'convert-close-bracket)
    ((eq line-type 'empty-line) #'convert-empty-line)
    (t #'convert-unknown))
)

(defun convert (line)
  "Convert a C line into Lisp code by applying the appropriate conversion function."
  (let ((line-type (line-type line)))
    (funcall (conversion-foo line-type) line))
)

(defun convert-c-to-lisp-recursive (lines)
  "Recursively convert each line of C code to Lisp code, handling variable declarations appropriately."
  (cond
    ((null lines) nil)
    ((member (line-type (car lines)) 
            '(variable-declaration variable-declaration-assignment
              variable-assignment variable-by-function))
     (let* ((var-lines '())
            (remaining-lines lines))
       (loop while (and remaining-lines 
                       (member (line-type (car remaining-lines))
                               '(variable-declaration variable-declaration-assignment
                                 variable-assignment variable-by-function)))
             do (push (car remaining-lines) var-lines)
                (setf remaining-lines (cdr remaining-lines)))
       (cons (convert-variable-assignments (reverse var-lines))
             (convert-c-to-lisp-recursive remaining-lines))))
    (t (cons (convert (car lines))
             (convert-c-to-lisp-recursive (cdr lines)))))
)

(defun convert-logical-arithmetic-operation (expression)
  "Convert logical and arithmetic operations to proper Lisp prefix notation."
  (let* ((tokens (cl-ppcre:split "\\s+" (string-trim " " expression))))
    (cond
      ((member (second tokens) '("<" ">" "<=" ">=" "==" "!=") :test #'string=)
       (format nil "(~a ~a ~a)" 
               (if (string= (second tokens) "==") "="
                   (if (string= (second tokens) "!=") "/="
                       (second tokens)))
               (first tokens)
               (third tokens)))
      ((member (second tokens) '("+" "-" "*" "/") :test #'string=)
       (format nil "(~a ~a ~a)" 
               (second tokens)
               (first tokens)
               (third tokens)))
      (t expression)))
)

(defun convert-function-declaration (line)
  "Convert a function declaration from C to Lisp."
  (cl-ppcre:register-groups-bind (return-type name params)
      ("(\\w+)\\s+(\\w+)\\s*\\((.*?)\\)\\s*;" line)
    (if name
        (let* ((param-list (mapcar (lambda (param)
                                      (let ((trimmed-param (string-trim " " param)))
                                        (first (cl-ppcre:split "\\s+" trimmed-param))))
                                    (cl-ppcre:split "," params)))
               (lisp-param-types (mapcar #'convert-type-to-lisp-version param-list)))
          (format nil "(declaim (ftype (function (~{~a~^ ~}) ~a) ~a))~%"
                  (mapcar #'string-downcase lisp-param-types)
                  (string-downcase (convert-type-to-lisp-version return-type))
                  name))
        (error "Error: Invalid function declaration line: ~a" line)))
)

(defun convert-type-to-lisp-version (type)
  (let ((lowercase-type (string-downcase type)))
    (cond
      ((string= lowercase-type "int") 'integer)
      ((string= lowercase-type "float") 'float)
      ((string= lowercase-type "double") 'double-float)
      ((string= lowercase-type "char") 'character)
      ((string= lowercase-type "void") 'void)
      (t (error "Unknown type: ~a" type))))
)

(defun convert-function-definition (line)
  "Convert a function definition from C to Lisp."
  (cl-ppcre:register-groups-bind (return-type name params)
      ("(\\w+)\\s+(\\w+)\\s*\\((.*?)\\)\\s*{" line)
    (if name
        (let* ((param-list (mapcar (lambda (param)
                                      (let ((trimmed-param (string-trim " " param)))
                                        (second (cl-ppcre:split "\\s+" trimmed-param))))
                                    (cl-ppcre:split "," params))))
          (format nil "(defun ~a (~{~a~^ ~})~%" name param-list))
        (error "Error: Invalid function definition line: ~a" line)))
)

(defun convert-variable-declaration (line)
  "Convert a standalone variable declaration from C to Lisp's setq format."
  (cl-ppcre:register-groups-bind (type name)
      ("\\b(\\w+)\\s+(\\w+)\\s*;" line)
    (if (and type name)
        (format nil "(~a 0)" name) 
        (format nil ";; Unable to parse standalone declaration: ~a~%" line)))
)

(defun convert-variable-assignment (line)
  "Convert a variable assignment with proper indentation."
  (cl-ppcre:register-groups-bind (name value)
      ("\\b(\\w+)\\s*=\\s*([^;]+);" line)
    (if (and name value)
        (let* ((trimmed-value (string-trim " " value))
               (tokens (cl-ppcre:split "\\s+" trimmed-value)))
          (if (> (length tokens) 1)
              (cond 
                ((member (first tokens) '("+" "-" "*" "/") :test #'string=)
                 (format nil "        (setf ~a (~a ~{~a~^ ~}))~%" 
                         name 
                         (first tokens)
                         (cdr tokens)))
                ((member (first tokens) '("<" ">" "<=" ">=" "==" "!=") :test #'string=)
                 (format nil "        (setf ~a (~a ~{~a~^ ~}))~%" 
                         name 
                         (cond ((string= (first tokens) "==") "=")
                               ((string= (first tokens) "!=") "/=")
                               (t (first tokens)))
                         (cdr tokens)))
                ((and (= (length tokens) 3)
                      (member (second tokens) '("+" "-" "*" "/" "<" ">" "<=" ">=" "==" "!=") :test #'string=))
                 (format nil "        (setf ~a (~a ~a ~a))~%" 
                         name
                         (cond ((string= (second tokens) "==") "=")
                               ((string= (second tokens) "!=") "/=")
                               (t (second tokens)))
                         (first tokens)
                         (third tokens)))
                (t (format nil "        (setf ~a ~a)~%" name trimmed-value)))
              (format nil "        (setf ~a ~a)~%" name trimmed-value)))
        (format nil "        ;; Unable to parse assignment: ~a~%" line)))
)

(defun convert-variable-by-function (line)
  "Convert a variable assignment that calls a function from C to Lisp."
  (cl-ppcre:register-groups-bind (var function args)
      ("\\b(\\w+)\\s*=\\s*(\\w+)\\s*\\((.*)\\);?" line)
    (if (and var function args)
        (format nil "(~a (~a ~{~a~^ ~}))" 
                var 
                function 
                (mapcar (lambda (arg) (string-trim " " arg)) (cl-ppcre:split "," args)))
        (format nil ";; Unable to parse variable by function assignment: ~a~%" line)))
)

(defun convert-variable-assignments (lines)
  "Convert consecutive variable declarations and assignments from C to either let or setq form."
  (let ((assignments '())
        (count 0))
    (loop for line in lines
          while (member (line-type line) '(variable-declaration variable-declaration-assignment
                                         variable-assignment variable-by-function))
          do (incf count))
    
    (if (= count 1)
        (let ((line (car lines)))
          (cond
            ((eq (line-type line) 'variable-declaration-assignment)
             (cl-ppcre:register-groups-bind (type name value)
                 ("\\b(\\w+)\\s+(\\w+)\\s*=\\s*([^;]+);" line)
               (let* ((trimmed-value (string-trim " " value))
                     (tokens (cl-ppcre:split "\\s+" trimmed-value)))
                 (if (> (length tokens) 1)
                     (cond
                       ((and (= (length tokens) 3)
                             (member (second tokens) '("+" "-" "*" "/" "<" ">" "<=" ">=" "==" "!=") :test #'string=))
                        (format nil "  (setf ~a (~a ~a ~a))~%" 
                                name
                                (cond ((string= (second tokens) "==") "=")
                                      ((string= (second tokens) "!=") "/=")
                                      (t (second tokens)))
                                (first tokens)
                                (third tokens)))
                       (t (format nil "  (setf ~a ~a)~%" name trimmed-value)))
                     (format nil "  (setf ~a ~a)~%" name trimmed-value)))))
            ((eq (line-type line) 'variable-by-function)
             (convert-variable-by-function line))
            ((eq (line-type line) 'variable-assignment)
             (convert-variable-assignment line))
            (t (convert-variable-declaration line))))
        
        (progn
          (loop for line in lines
                while (member (line-type line) '(variable-declaration variable-declaration-assignment
                                               variable-assignment variable-by-function))
                do (let ((converted
                         (cond
                           ((eq (line-type line) 'variable-declaration-assignment)
                            (cl-ppcre:register-groups-bind (type name value)
                                ("\\b(\\w+)\\s+(\\w+)\\s*=\\s*([^;]+);" line)
                              (let* ((trimmed-value (string-trim " " value))
                                    (tokens (cl-ppcre:split "\\s+" trimmed-value)))
                                (if (> (length tokens) 1)
                                    (format nil "(~a (~a ~{~a~^ ~}))" 
                                            name
                                            (if (member (second tokens) '("==" "!=") :test #'string=)
                                                (if (string= (second tokens) "==") "=" "/=")
                                                (second tokens))
                                            (list (first tokens) (third tokens)))
                                    (format nil "(~a ~a)" name trimmed-value)))))
                           ((eq (line-type line) 'variable-by-function)
                            (convert-variable-by-function line))
                           ((eq (line-type line) 'variable-assignment)
                            (cl-ppcre:register-groups-bind (name value)
                                ("\\b(\\w+)\\s*=\\s*([^;]+);" line)
                              (let* ((trimmed-value (string-trim " " value))
                                    (tokens (cl-ppcre:split "\\s+" trimmed-value)))
                                (if (> (length tokens) 1)
                                    (format nil "(~a (~a ~{~a~^ ~}))" 
                                            name
                                            (if (member (second tokens) '("==" "!=") :test #'string=)
                                                (if (string= (second tokens) "==") "=" "/=")
                                                (second tokens))
                                            (list (first tokens) (third tokens)))
                                    (format nil "(~a ~a)" name trimmed-value)))))
                           (t (convert-variable-declaration line)))))
                     (push converted assignments)))
          (if assignments
              (format nil "  (let (~{~a~^~%        ~})~%  )" (reverse assignments))
              nil))))
)

(defun convert-print-function-variable (line)
  "Convert printf with variables to format with proper indentation."
  (let* ((parts (cl-ppcre:split "\"" line))
         (literal (second parts))
         (after-literal (third parts))
         (variable (when after-literal 
                    (string-trim " " (first (cl-ppcre:split "\\)" 
                                          (second (cl-ppcre:split "," after-literal)))))))
         (format-string (replace-percent (string-trim " " literal))))
    (if variable
        (format nil "        (format t \"~a\" ~a)~%" format-string variable)
        (format nil "        (format t \"~a\")~%" format-string)))
)

(defun replace-percent (input-string)
  "Replace '%' characters in the input string with '~'."
  (let ((result (make-string (length input-string))))
    (loop for i from 0 below (length input-string)
          do (setf (char result i)
                   (if (char= (char input-string i) #\%)
                       #\~  
                       (char input-string i))))
    result)
)

(defun convert-print-function-literal (line)
  "Convert printf with just literals to format with proper indentation."
  (let* ((parts (cl-ppcre:split "\"" line))
         (literal (second parts))
         (format-string (replace-percent (string-trim " " literal))))
    (format nil "        (format t \"~a\")~%" format-string))
)

(defun convert-return-value (line)
  "Convert a return statement from C to Lisp, converting infix to prefix notation."
  (let* ((value (cl-ppcre:regex-replace "return\\s+" (first (cl-ppcre:split ";" line)) ""  ))
         (trimmed-value (string-trim " " value))
         (elements (cl-ppcre:split "\\s+" trimmed-value)))
        (if (= (length elements) 3)
          (format nil "(~a ~a ~a)" (second elements) (first elements) (third elements))
          (format nil "(~a)" trimmed-value))
        (if (= (length elements) 5)
          (format nil "   (~a ~a ~a ~a ~a)" (nth 3 elements) (nth 1 elements) (nth 0 elements) (nth 2 elements) (nth 4 elements))
          (format nil "   (~a)" trimmed-value)))
)

(defvar *in-if-block* nil)

(defun convert-if-statement (line)
  "Convert an if statement from C to Lisp, with proper indentation and progn block."
  (setf *in-if-block* t)  ; Set the flag when entering an if block
  (let* ((trimmed-line (string-trim " " line))
         (start (search "(" trimmed-line))
         (end (search ")" trimmed-line))
         (condition (if (and start end) (subseq trimmed-line (1+ start) end) nil))
         (clean-condition (string-trim " " condition)))
    (let ((converted-condition (convert-logical-arithmetic-operation clean-condition)))
      (format nil "   (if ~a~%      (progn~%" converted-condition))))

(defun convert-for-loop (line)
  "Convert a for loop from C to Lisp."
  (let* ((trimmed-line (string-trim " " line))
         (start (search "(" trimmed-line))
         (end (search ")" trimmed-line))
         (expression (if (and start end) (subseq trimmed-line (1+ start) end) nil))
         (parts (cl-ppcre:split "[();]" expression))
         (initialization (string-trim " " (nth 0 parts)))
         (condition (string-trim " " (nth 1 parts)))
         (increment (string-trim " " (nth 2 parts))))
    (let* ((init-parts (cl-ppcre:split "\\s+" initialization))
           (var (second init-parts))
           (init-value (fourth init-parts)))
      (let 
      ((limit (first (cl-ppcre:split "\\s*<\\s*" condition))))
        (if (cl-ppcre:scan "\\+\\+" increment)
            (format nil "   (loop for ~a from ~a below ~a do~%" var init-value limit)
            (format nil "   (loop for ~a from ~a to ~a do~%" var init-value limit)
        ))))
)

(defun convert-while-loop (line)
  "Convert a while loop from C to a loop while in Lisp."
  (let* ((trimmed-line (string-trim " " line))
         (start (search "(" trimmed-line))
         (end (search ")" trimmed-line))
         (condition (if (and start end) (subseq trimmed-line (1+ start) end) nil))
         (clean-condition (string-trim " " condition)))
    (let ((converted-condition (convert-logical-arithmetic-operation clean-condition)))
      (format nil "    (loop while (~a) do~%" converted-condition)))
)

(defun convert-close-bracket (line)
  "Handle close braces by ending blocks in Lisp with proper indentation."
  (if *in-if-block*
      (progn
        (setf *in-if-block* nil)  ; Reset the flag
        (format nil "      ))~%"))
      (format nil ")~%")))

(defun convert-empty-line (line)
  "Preserve empty lines in the Lisp code."
  (format nil "~%")
)

(defun convert-unknown (line)
  "Handle unknown lines in the C code."
  (format nil ";; Unknown line: ~a~%" line)
)

(defun read-file-recursive (stream &optional acc)
  "Recursively read lines from a stream and return them in order.
   ACC accumulates the lines in reverse order."
  (let ((line (read-line stream nil nil)))
    (if line
        (read-file-recursive stream (cons line acc))
        (nreverse acc))))

(defun read-file (file)
  "Read the C code from a file using recursive approach."
  (with-open-file (stream file)
    (read-file-recursive stream)))

(defun write-file (file content)
  "Write the generated Lisp code to a file."
  (with-open-file (stream file :direction :output :if-exists :supersede :element-type 'character)
    (dolist (line content)
      (format stream "~a" line)))
) 

(defun convert-c-to-lisp (input-file output-file)
  "Convert C code from INPUT-FILE to Lisp code and write to OUTPUT-FILE recursively."
  (let ((c-lines (read-file input-file))
        (lisp-output '()))
    (setf lisp-output (convert-c-to-lisp-recursive c-lines)) 
    (write-file output-file lisp-output))
)

(convert-c-to-lisp "input.c" "output.lisp")