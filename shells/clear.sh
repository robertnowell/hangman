osascript 	-e 'tell application "terminal" to activate' \
-e 'tell application "System Events" to tell process "terminal" to keystroke "]" using {shift down, command down}' \
-e 'tell application "System Events" to tell process "terminal" to keystroke "c" using control down'\
-e 'tell application "System Events" to tell process "terminal" to keystroke "[" using {shift down, command down}'