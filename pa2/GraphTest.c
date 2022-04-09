// James Tennant • jtennant • 1773814

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
// 0123456789012345678901234567890123456789012345678901234567890123456789
	// From GraphClient.c  
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
	"Radius=%d\n",min);printf("Centralvert%s:",length(C)==1?"ex":
	"ices");printList(stdout,C);printf("\n");printf("Diameter=%d\n",
	max);printf("Peripheralvert%s:",length(P)==1?"ex":"ices");
	printList(stdout,P);printf("\n");freeList(&C);freeList(&P);
	freeList(&E);freeGraph(&G);

	return 0;
}
