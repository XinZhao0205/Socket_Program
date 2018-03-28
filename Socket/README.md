A: 	Xin Zhao

****************************************************************************************************************************************
C:  	This project asks us to build a simple model of computational offloading. We have one client, one edge server and two backened server.The edge server and client are connected through TCP,and the edge server and all backened servers are connected through UDP. The task for this model is, when the client uploads "and" and "or" data, the edge server will split the "and" and "or" data and pass them to the backened and server and backened or server. After backened servers finish their calculating, they will through UDP send the result to the edge server. And the edge server will send the result to client server. 

****************************************************************************************************************************************
D: 	There are 4 code files, they are client.c, edge.c,  server_and.c, server_or.c.

  	client.c: The client will first read the data from the given file, and send the file to the edge through TCP. And finally show the result sended from the edge.

	edge.c: The edge server is the bridge between client and backened servers. It will set up connections between both client and backened servers. The works for edge server is splited the "and" and "or" data, send then to the backened_and and backened_or server seperately through UDP. After reciving the backened server result, edge server will send the result to the client through TCP.

	server_and.c, server_or.c: These are backened server. They will receive the data transmitted from the edge through UDP. And do "and" and "or" caculating. Then they send the result to edge server through UDP. 

***************************************************************************
E:	a. Open the document which contains 5 files, they are "makefile"  "client.c"  "edge.c"  "server_and.c"  "server_or.c"
	b. Open 4 terminals. In the first terminal,input command "make all" in one of the terminal. Then input "make edge" "make server_and" "make server_or" in other 3 terminals. Then input "./client (text file name)" in the first terminal. 
	c. Then the result will show on the screen.

NOTICE: In my code, there are some warnings. But some of them come from the video which the professor gives us (I reference the TCP and UDP code from that) and I cannot exactly find the probelm.

******************************************************************************
F: 	C language
        Linux system

******************************************************************************
G: 	In my program, I think I meet all the requirements.

******************************************************************************** 
H:	The code of the  UDP and TCP communication parts come from the Video and the book named "Beej's Guide to Network Programming". 
From the website:
	https://www.youtube.com/watch?v=V6CohFrRNTo  
	WWW.beej.us/guide/bgc/output/print/bgc_USLetter.pdf 



			

