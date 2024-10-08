M501 ; Load settings from EEPROM
G21 ; Set millimeter unit
G90 ; Set all axes to absolute
G28 ; Home all axes
M413 S0 ; Disable power loss recovery
G29 A ; Enable mesh bed leveling
M569 S0 E ; Spreadcycle mode for extruder
G0 X0.0 Y0.0 F3000 ; Move to point 0
G92 E0 ; Reset extruder
M140 S60 ; Start heating bed
M104 S220 ; Start heating extruder
M190 S60 ; Wait heating bed
M109 S220 ; Wait heating extruder
G1 Z0.2 E15 F600 ; Move to layer height and extrude material
G0 X2.0 Y0.0 F3000 ; Move to point 1
G1 X2.0 Y180.0 E30 F3000 ; Extrude material until point 2
G0 X2.4 Y180.0 F3000 ; Move to point 3
G1 X2.4 Y10.0 E45 F3000 ; Extrude material until point 4
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
;
; print anchor frame
;
G1 X78.5 Y82 F12000 ; move to start
G1 X78.5 Y128 E2.0196 F2400 ; print line
G1 X78.98 Y128 F12000 ; move to start
G1 X78.98 Y82 E2.0196 F2400 ; print line
G1 E-1.5 F7200 ; retract
G1 X158.5 Y82 F12000 ; move to start
G1 E1.5 F7200 ; un-retract
G1 X158.5 Y128 E2.0196 F2400 ; print line
G1 X158.02 Y128 F12000 ; move to start
G1 X158.02 Y82 E2.0196 F2400 ; print line
G1 E-1.5 F7200 ; retract
;
; start the Test pattern
;
G4 P2000 ; Pause (dwell) for 2 seconds
G1 X78.5 Y85 F12000 ; move to start
M900 K0 ; set K-factor
M117 K0 ; 
G1 E1.5 F7200 ; un-retract
G1 X98.5 Y85 E0.7982 F2400 ; print line
G1 X138.5 Y85 E1.5965 F12000 ; print line
G1 X158.5 Y85 E0.7982 F2400 ; print line
G1 E-1.5 F7200 ; retract
G1 X78.5 Y89 F12000 ; move to start
M900 K0.01 ; set K-factor
M117 K0.01 ; 
G1 E1.5 F7200 ; un-retract
G1 X98.5 Y89 E0.7982 F2400 ; print line
G1 X138.5 Y89 E1.5965 F12000 ; print line
G1 X158.5 Y89 E0.7982 F2400 ; print line
G1 E-1.5 F7200 ; retract
G1 X78.5 Y93 F12000 ; move to start
M900 K0.02 ; set K-factor
M117 K0.02 ; 
G1 E1.5 F7200 ; un-retract
G1 X98.5 Y93 E0.7982 F2400 ; print line
G1 X138.5 Y93 E1.5965 F12000 ; print line
G1 X158.5 Y93 E0.7982 F2400 ; print line
G1 E-1.5 F7200 ; retract
G1 X78.5 Y97 F12000 ; move to start
M900 K0.03 ; set K-factor
M117 K0.03 ; 
G1 E1.5 F7200 ; un-retract
G1 X98.5 Y97 E0.7982 F2400 ; print line
G1 X138.5 Y97 E1.5965 F12000 ; print line
G1 X158.5 Y97 E0.7982 F2400 ; print line
G1 E-1.5 F7200 ; retract
G1 X78.5 Y101 F12000 ; move to start
M900 K0.04 ; set K-factor
M117 K0.04 ; 
G1 E1.5 F7200 ; un-retract
G1 X98.5 Y101 E0.7982 F2400 ; print line
G1 X138.5 Y101 E1.5965 F12000 ; print line
G1 X158.5 Y101 E0.7982 F2400 ; print line
G1 E-1.5 F7200 ; retract
G1 X78.5 Y105 F12000 ; move to start
M900 K0.05 ; set K-factor
M117 K0.05 ; 
G1 E1.5 F7200 ; un-retract
G1 X98.5 Y105 E0.7982 F2400 ; print line
G1 X138.5 Y105 E1.5965 F12000 ; print line
G1 X158.5 Y105 E0.7982 F2400 ; print line
G1 E-1.5 F7200 ; retract
G1 X78.5 Y109 F12000 ; move to start
M900 K0.06 ; set K-factor
M117 K0.06 ; 
G1 E1.5 F7200 ; un-retract
G1 X98.5 Y109 E0.7982 F2400 ; print line
G1 X138.5 Y109 E1.5965 F12000 ; print line
G1 X158.5 Y109 E0.7982 F2400 ; print line
G1 E-1.5 F7200 ; retract
G1 X78.5 Y113 F12000 ; move to start
M900 K0.07 ; set K-factor
M117 K0.07 ; 
G1 E1.5 F7200 ; un-retract
G1 X98.5 Y113 E0.7982 F2400 ; print line
G1 X138.5 Y113 E1.5965 F12000 ; print line
G1 X158.5 Y113 E0.7982 F2400 ; print line
G1 E-1.5 F7200 ; retract
G1 X78.5 Y117 F12000 ; move to start
M900 K0.08 ; set K-factor
M117 K0.08 ; 
G1 E1.5 F7200 ; un-retract
G1 X98.5 Y117 E0.7982 F2400 ; print line
G1 X138.5 Y117 E1.5965 F12000 ; print line
G1 X158.5 Y117 E0.7982 F2400 ; print line
G1 E-1.5 F7200 ; retract
G1 X78.5 Y121 F12000 ; move to start
M900 K0.09 ; set K-factor
M117 K0.09 ; 
G1 E1.5 F7200 ; un-retract
G1 X98.5 Y121 E0.7982 F2400 ; print line
G1 X138.5 Y121 E1.5965 F12000 ; print line
G1 X158.5 Y121 E0.7982 F2400 ; print line
G1 E-1.5 F7200 ; retract
G1 X78.5 Y125 F12000 ; move to start
M900 K0.1 ; set K-factor
M117 K0.1 ; 
G1 E1.5 F7200 ; un-retract
G1 X98.5 Y125 E0.7982 F2400 ; print line
G1 X138.5 Y125 E1.5965 F12000 ; print line
G1 X158.5 Y125 E0.7982 F2400 ; print line
G1 E-1.5 F7200 ; retract
G1 X78.5 Y129 F12000 ; move to start
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