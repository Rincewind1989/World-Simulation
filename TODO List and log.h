#pragma once

/*
-Make all constants changeable by the organism (E.g. needed energy for offspring)
-All equations have all variables in it with constants and exponentials which can be written in a second config file

19.08.2018
-Organisms still don't have a real evolution. Have to find right parameters.
25.11.2018
-The border of the map now does not have any food. This prevents from crowding the borders. The more beautiful solution would be to find a right set of equations/parameters that gives advantage for staying inland. (Maybe try an island setup?)
-There seems to be too much random behavior. I guess the parameter space is just too big. Maybe i should try a slim version where there is only food with a easy set of parameters. (Maybe try that while moving an organism can't eat?)
8.12.2018
-Changing the movement behavior and visuals of the organisms. Instead of a fixed coordinate system, lets try a relative one, where the organisms can rotate. Makes more sense.
-Implement simple food and temperature rules. ODEs are computational costly.



*/