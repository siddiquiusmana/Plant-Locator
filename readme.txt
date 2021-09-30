Project: Herb Locator

A simple program that takes your location and that of the herbs and sorts them in order
from closest to farthest using a mash of Merge Sort and Insertion Sort. The program also has
a built in query processor so that you can ask whether a herb exist at a certain point.

The input is formatted as follows:

------------------------------------------
#x #y #ofMonsters #ofQueries #Threshold

#xofMonster1 #yofMonster1
#xofMonster2 #yofMonster2
#xofMonster3 #yofMonster3
[...]
#xofMonster# #yofMonster#

#xofQuery1 #yofQuery1
#xofQuery2 #yofQuery2
#xofQuery3 #yofQuery3
[...]
#xofQuery# #yofQuery#

------------------------------------------

Where, all # are positive integers only.

The program scans and sorts #ofMonsters using a mash of merge and insert sort. #Threshold
informs the program of the maximum size of an array, insertion sort can be ran on. Any array larger
than that size is handled by Merge Sort. 