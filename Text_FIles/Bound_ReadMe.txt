"baker" = big circle
"oven" = end portal
"bread" = little guys

OBJECTIVE:
	Get the "baker" to the "oven" using bread to complete the stage and move onto the next

HOW TO PLAY:
	- Cursor automatically starts on baker
	- Since baker is useless alone, he needs the bread to help him reach the oven
	- Each piece of bread has different abilities to help the baker across each stage
	- Baker can choose which size of bread he wants to use. 


CONTROLS:
	- Moving : w/a/s/d
	- Shooting bread : spacebar 
	- To cycle between bread : tab
	- Pause - p
	- Reset - r
	- Switch characters - left click
	- Move around cursor - mouse position
	- Abilitiy activation - right click (hold/press)

GAME FEATURES:
	- Power bar for firing power of bread (either hold space or toggle)
	- Trajectory is based on position of arrow + power of powerbar 
	- If all bread is used, player can choose to restart game
	- Internal time limit - depends on stage
	- Pause / Reset
	- The Box Formulae
		• Total Charge starts at 3. Increments by 1 for every switch hit.
		• Inert Charge == current switch hit. 1, 2 or 3.

		Charge Placement Formula: [(Total•1)-Inert]%9, [(Total•2)-Inert]%9, [(Total•3)-Inert]%9
		Baker Placement Formula: [Current Position+Inert]%9
 


GAME BREAD ABILITIES:
	- The Baker: Basic motion. Reaches 'oven' to complete stage. Interacts with each bread in different ways to solve puzzles and progress. 
	- Roti: Power of attraction/repulsion. Can push or pull The Baker away from it. Only means of moving upwards in game.
	- Anpan: Power of displacement. Can switch positions with the Baker. *To implement, programming-wise, check to make sure parallel sides of The Baker's new position are not colliding. If they are, then displacement does not occur.
	- Boule: Power of Distortion. Can enter ‘negative zone’ when the right click is pressed. In the negative zone, portals appear which can teleport Boule between the portal and the corresponding character (Baker inclusive). Can see - and thus activate - switches that are in negative zone.