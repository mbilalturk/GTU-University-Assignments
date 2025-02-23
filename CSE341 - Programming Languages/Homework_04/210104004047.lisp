(defun variable-p (str)
  (and (stringp str)
       (char<= #\A (char str 0) #\Z)))

(defun lookup-var (var bindings)
  (if (null bindings)
      var
      (let ((pair (assoc var bindings :test #'string=)))
        (if pair
            (second pair)
            var))))

(defun unify (pred1 pred2 bindings)
  (if (or (not (= (length pred1) (length pred2)))
          (not (string= (first pred1) (first pred2))))
      nil
      (let ((new-bindings bindings))
        (loop for term1 in (rest pred1)
              for term2 in (rest pred2)
              do (let* ((val1 (lookup-var term1 new-bindings))
                       (val2 (lookup-var term2 new-bindings)))
                   (cond ((string= val1 val2))
                         ((variable-p val1)
                          (setf new-bindings (cons (list val1 val2) new-bindings)))
                         ((variable-p val2)
                          (setf new-bindings (cons (list val2 val1) new-bindings)))
                         (t (return-from unify nil)))))
        new-bindings)))

(defun prove-goal (goals axioms bindings depth)
  (cond ((> depth 20) nil)
        ((null goals) (list bindings))
        (t (let* ((goal (first goals))
                  (rest-goals (rest goals))
                  (all-results nil))
             (dolist (axiom axioms)
               (if (= (length axiom) 1)
                   (let ((new-bindings (unify goal (first axiom) bindings)))
                     (when new-bindings
                       (let ((result (prove-goal rest-goals axioms new-bindings (1+ depth))))
                         (when result
                           (setf all-results (append all-results result))))))
                   (let ((new-bindings (unify goal (first axiom) bindings)))
                     (when new-bindings
                       (let ((result (prove-goal (append (cddr axiom) rest-goals)
                                               axioms
                                               new-bindings
                                               (1+ depth))))
                         (when result
                           (setf all-results (append all-results result))))))))
             all-results))))

(defun prolog_prove (axioms query)
  (let ((results (prove-goal query axioms nil 0)))
    (if results
        (remove-duplicates
         (loop for bindings in results
               append (loop for pred in query
                          append (loop for term in (rest pred)
                                     when (variable-p term)
                                     collect (list (format nil "\"~A\"" term) 
                                                 (format nil "\"~A\"" (lookup-var term bindings))))))
         :test #'equal)
        nil)))

(let* ((axioms '(
                 (("father" "jim" "jill"))
                 (("mother" "mary" "jill"))
                 (("father" "samm" "jim"))
                 (("ancestor" "X" "Y") "<" ("parent" "X" "Y")) 
                 (("ancestor" "X" "Y") "<" ("parent" "X" "Z") ("ancestor" "Z" "Y"))
                 (("parent" "X" "Y") "<" ("mother" "X" "Y"))
                 (("parent" "X" "Y") "<" ("father" "X" "Y"))))
       (query1 '(("ancestor" "X" "jill")))
       (result (prolog_prove axioms query1)))
  (format t "~A~%" result))