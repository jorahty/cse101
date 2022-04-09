// James Tennant • jtennant • pa2

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(void){

	// Run the test from GraphClient.c (compressed) 
	printf("\033[0;32m");
	int i,s,max,min,d,n=35;List C=newList();List P=newList();List E=
	newList();Graph G=NULL;G=newGraph(n);for(i=1;i<n;i++){if(i%7!=0){
	addEdge(G,i,i+1);}if(i<=28){addEdge(G,i,i+7);}}addEdge(G,9,31);
	addEdge(G,17,13);addEdge(G,14,33);printGraph(stdout,G);for(s=1;s
	<=n;s++){BFS(G,s);max=getDist(G,1);for(i=2;i<=n;i++){d=
	getDist(G,i);max=(max<d?d:max);}append(E,max);}append(C,1);
	append(P,1);min=max=front(E);moveFront(E);moveNext(E);for(i=2;i<=n
	;i++){d=get(E);if(d==min){append(C,i);}else if(d<min){min=d;
	clear(C);append(C,i);}if(d==max){append(P,i);}else if(d>max){max=d;
	clear(P);append(P,i);}moveNext(E);}printf("\n");printf(
	"Radius = %d\n",min);printf("Central vert%s: ",length(C)==1?"ex":
	"ices");printList(stdout,C);printf("\n");printf("Diameter = %d\n",
	max);printf("Peripheral vert%s: ",length(P)==1?"ex":"ices");
	printList(stdout,P);printf("\n");freeList(&C);freeList(&P);
	freeList(&E);freeGraph(&G);printf("\033[0m\n");

	// Run the example from lecture
	G = newGraph(6);
	addEdge(G, 1, 2); 
	addEdge(G, 1, 3); 
	addEdge(G, 2, 4); 
	addEdge(G, 2, 5); 
	addEdge(G, 2, 6); 
	
	freeGraph(&G);	

	return 0;
}
