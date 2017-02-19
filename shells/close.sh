osascript 	-e 'tell application "terminal" to activate' \
			-e 'tell application "System Events" to tell process "terminal" to keystroke "]" using {shift down, command down}' \
			-e 'tell application "System Events" to tell process "terminal" to keystroke "c" using control down'\
			-e 'tell application "System Events" to tell process "terminal" to keystroke "w" using command down'
			# -e 'tell application "System Events" to tell process "terminal" to key code 52' \
			# -e 'tell application "System Events" to tell process "terminal" to keystroke "[" using {shift down, command down}'