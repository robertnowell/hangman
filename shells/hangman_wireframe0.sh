osascript -e 'tell application "terminal" to activate' \
-e 'tell application "System Events" to tell process "terminal" to keystroke "t" using command down' \
-e 'tell application "System Events" to tell process "terminal" to keystroke "./wireframe 0.fdf"' \
-e 'tell application "System Events" to tell process "terminal" to key code 52' \
-e 'tell application "System Events" to tell process "terminal" to keystroke "[" using {shift down, command down}'