# Route-Manager
The route_manager.c program takes an command line input from the user, where the arguments act as filters for the airline route data contained in airline-routes-data.csv. This program can take 3 different user input cases.

**CASE 1:**
  Command: ./route_manager --DATA="airline-routes-data.csv" --AIRLINE="*enter airline*" --DEST_COUNTRY="*enter destination country*"  
  Output: The output of the routes that match these filters would be outputted in the output.txt file.

**Case 2:**
  Command: ./route_manager --DATA="airline-routes-data.csv" --SRC_COUNTRY="enter source country" --DEST_CITY="enter destination city" --DEST_COUNTRY="Enter destination country"  
  Output: The output of the routes that match these filters would be outputted in the output.txt file.

**Case 3:**
  Command: ./route_manager --DATA="airline-routes-data.csv" --SRC_CITY="enter source city" --SRC_COUNTRY="enter source country" --DEST_CITY="enter destination city" --DEST_COUNTRY="enter destination country"  
  Output: The output of the routes that match these filters would be outputted in the output.txt file.


  
  
