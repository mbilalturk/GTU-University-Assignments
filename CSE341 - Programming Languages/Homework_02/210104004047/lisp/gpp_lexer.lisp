/*
To run: make (terminate by entering "quit") 
*/

(defconstant +keywords+
  '(("and" . "KW_AND") ("or" . "KW_OR") ("not" . "KW_NOT")
    ("equal" . "KW_EQUAL") ("less" . "KW_LESS") ("nil" . "KW_NIL")
    ("list" . "KW_LIST") ("append" . "KW_APPEND") ("concat" . "KW_CONCAT")
    ("set" . "KW_SET") ("deffun" . "KW_DEFFUN") ("for" . "KW_FOR")
    ("if" . "KW_IF") ("exit" . "KW_EXIT") ("load" . "KW_LOAD")
    ("print" . "KW_PRINT") ("true" . "KW_TRUE") ("false" . "KW_FALSE")))

(defconstant +operators+
  '(("+" . "OP_PLUS") ("-" . "OP_MINUS") ("/" . "OP_DIV")
    ("*" . "OP_MULT") ("(" . "OP_OP") (")" . "OP_CP")
    ("," . "OP_COMMA")))

(defun whitespace-char-p (char)
  (member char '(#\Space #\Tab #\Newline #\Return)))

(defun operator-char-p (char)
  (member char '(#\+ #\- #\/ #\* #\( #\) #\,)))

(defun extract-comment (line pos)
  (when (and (< (1+ pos) (length line))
             (char= (char line pos) #\;)
             (char= (char line (1+ pos)) #\;))
    (values "COMMENT" (length line))))

(defun extract-operator (line pos)
  (when (< pos (length line))
    (let ((op (string (char line pos))))
      (values (cdr (assoc op +operators+ :test #'string=))
              (1+ pos)))))

(defun extract-identifier-or-keyword (line pos)
  (let ((start pos))
    (loop while (and (< pos (length line))
                    (or (alphanumericp (char line pos))
                        (char= (char line pos) #\_)))
          do (incf pos))
    (let* ((token-str (subseq line start pos))
           (keyword (assoc token-str +keywords+ :test #'string=)))
      (values (if keyword 
                  (cdr keyword)
                  "IDENTIFIER")
              pos))))

(defun extract-number (line pos)
  (let ((start pos))
    (loop while (and (< pos (length line))
                    (digit-char-p (char line pos)))
          do (incf pos))
    (if (and (< pos (length line))
             (char= (char line pos) #\f))
        ;; Handle fraction
        (progn
          (incf pos)
          (let ((frac-start pos))
            (loop while (and (< pos (length line))
                           (digit-char-p (char line pos)))
                  do (incf pos))
            (values "VALUEF" pos)))
        ;; Regular integer
        (values "VALUEI" pos))))

(defun tokenize-line (line)
  (let ((pos 0)
        (tokens nil))
    (handler-case
        (loop while (< pos (length line))
              do (let ((char (char line pos)))
                   (cond
                     ((whitespace-char-p char)
                      (incf pos))
                     
                     ((char= char #\;)
                      (multiple-value-bind (token new-pos)
                          (extract-comment line pos)
                        (when token
                          (push token tokens))
                        (setf pos new-pos)))
                     
                     ((operator-char-p char)
                      (multiple-value-bind (token new-pos)
                          (extract-operator line pos)
                        (push token tokens)
                        (setf pos new-pos)))
                     
                     ((digit-char-p char)
                      (multiple-value-bind (token new-pos)
                          (extract-number line pos)
                        (push token tokens)
                        (setf pos new-pos)))
                     
                     ((alpha-char-p char)
                      (multiple-value-bind (token new-pos)
                          (extract-identifier-or-keyword line pos)
                        (push token tokens)
                        (setf pos new-pos)))
                     
                     (t
                      ;; Print existing tokens and syntax error
                      (dolist (token (reverse tokens))
                        (format t "~A~%" token))
                      (format t "SYNTAX_ERROR~%")
                      (return-from tokenize-line nil)))))
      (error (e)
        (format t "Error: ~A~%" e)
        (return-from tokenize-line nil)))
    (reverse tokens)))

(defun gppinterpreter (&optional filename)
  (if filename
      ;; File mode
      (with-open-file (stream filename)
        (loop for line = (read-line stream nil)
              while line
              do (let ((tokens (tokenize-line line)))
                   (when tokens 
                     (dolist (token tokens)
                       (format t "~A~%" token))))))
      ;; Interactive mode
      (loop
        (format t "> ")
        (force-output)
        (let ((line (read-line nil nil)))
          (when (or (null line) (string= line "quit"))
            (return))
          (let ((tokens (tokenize-line line)))
            (when tokens 
              (dolist (token tokens)
                (format t "~A~%" token))))))))

(gppinterpreter "input.g++")
(gppinterpreter)