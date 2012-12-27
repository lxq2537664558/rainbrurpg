(define name "Test")
(define version "0.0.0")
(define depends (list "aze > 3" "ert >2"))

(define init-service
  ((format #t "Starting service '~a'~%" name)
   (service-name myname)))