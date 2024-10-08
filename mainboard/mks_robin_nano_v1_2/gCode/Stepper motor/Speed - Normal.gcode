M501 ; Load settings from EEPROM
G21 ; Set millimeter unit
G90 ; Set all axes to absolute
G28 ; Home all axes
M413 S0 ; Disable power loss recovery
G29 A ; Enable mesh bed leveling
M569 S0 E ; Spreadcycle mode for extruder
G0 X0.0 Y0.0 F3000 ; Move to point 0
G92 E0 ; Reset extruder
; ---
M117 Prepare
M83 ; Relative E
G0 F7500 ; Set feedrate to 125mm/s
M201 X5000 Y5000 ; Set max acceleration
M203 X300 Y300 ; Set max feedrate
M204 S5000 ; Set default acceleration for print and travel
M205 J0.024 ; Junction deviation
G1 Z0.2 F600 ; Move to layer height
G92 E0 ; Reset extruder
; ---
M117 Start step 1
G0 X45 Y45
G0 X70 Y35
G0 X95 Y45
G0 X105 Y70
G0 X95 Y95
G0 X70 Y105
G0 X45 Y95
G0 X35 Y70
M117 Start step 2
G0 X45 Y95
G0 X70 Y105
G0 X95 Y95
G0 X105 Y70
G0 X95 Y45
G0 X70 Y35
G0 X45 Y45
G0 X35 Y70
M117 Start step 3
G0 X70 Y70
G0 X45 Y45
G0 X70 Y70
G0 X70 Y35
G0 X70 Y70
G0 X95 Y45
G0 X70 Y70
G0 X105 Y70
G0 X70 Y70
G0 X95 Y95
G0 X70 Y70
G0 X70 Y105
G0 X70 Y70
G0 X45 Y95
G0 X70 Y70
G0 X35 Y70
M117 Start step 4
G0 X70 Y70
G0 X45 Y95
G0 X70 Y70
G0 X70 Y105
G0 X70 Y70
G0 X95 Y95
G0 X70 Y70
G0 X105 Y70
G0 X70 Y70
G0 X95 Y45
G0 X70 Y70
G0 X70 Y35
G0 X70 Y70
G0 X45 Y45
G0 X70 Y70
G0 X35 Y70
M117 Complete
M400 ; Wait move to finish
; ---
M501 ; Load settings from EEPROM
M900 K0 ; Disable linear advance
G91 ; Set all axes to relative
G0 Z10.0 F600 ; Up Z axis
G90 ; Set all axes to absolute
G0 X0.0 Y0.0 F3000 ; Move to point 0
G92 E0 ; Reset extruder
M84 X Y Z E ; Turn off all motors
M104 S0 ; Turn off extruder
M140 S0 ; Turn off bed
M106 S0 ; Turn off fan