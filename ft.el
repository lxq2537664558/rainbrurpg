;; Trying to compute and print FT automagically
; open a file, process it, save, close it
(defun print-ft (fpath)
  "process the file at fullpath FPATH ..."
  (let (mybuffer)
    (setq mybuffer (find-file fpath))
    (goto-char (point-min)) ;; in case buffer already open

    ;; compute total FT 
    (org-clock-display)
;;    (princ (format "%s\n" (org-clock-display)));; (get-buffer "*scratch*"))

    (save-buffer)
    (kill-buffer mybuffer)))

(print-ft "roadmap-temp-file-for-sum")