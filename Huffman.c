#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TREE_HT 100

#define MAX_CHARACTERS 256
typedef struct {
    int val;
    char letra;
    char x[100];
} L;

void contarCaracteres(const char *cadena, L* h) {
    int longitud = strlen(cadena);
    int contador[MAX_CHARACTERS] = {0};
	int i,j;
	int k=0;
    // Contar la frecuencia de cada carácter en la cadena
    for (i = 0; i < longitud; i++) {
        contador[(int)cadena[i]]++;
			
		 
        
    }

    // Mostrar los resultados
    printf("Caracter\tFrecuencia\n");
    int v=0;
    for (i = 0; i < MAX_CHARACTERS; i++) {
        if (contador[i] > 0) {
            printf("%c\t\t%d\n", i, contador[i]);
			h[v].letra=(char)i;
			h[v].val=contador[i];
			
			v++;
        }
    }
}
 int cUnicos(const char* str) {
    // Arreglo booleano para realizar un seguimiento de los caracteres encontrados
    int found[256] = {0};
    int unico = 0;
	int i;
    // Recorrido de la cadena de caracteres
    for (i = 0; str[i] != '\0'; i++) {
        // Verificar si el carácter ya ha sido encontrado
        if (!found[(unsigned char)str[i]]) {
            found[(unsigned char)str[i]] = 1;
            unico++;
        }
    }

    return unico;
}


//-------------------------------------------------------------------------------
struct MinHeapNode {

	// One of the input characters
	char data;

	// Frequency of the character
	unsigned freq;

	// Left and right child of this node
	struct MinHeapNode *left, *right;
};

// A Min Heap: Collection of
// min-heap (or Huffman tree) nodes
struct MinHeap {

	// Current size of min heap
	unsigned size;

	// capacity of min heap
	unsigned capacity;

	// Array of minheap node pointers
	struct MinHeapNode** array;
};

// A utility function allocate a new
// min heap node with given character
// and frequency of the character
struct MinHeapNode* newNode(char data, unsigned freq)
{
	struct MinHeapNode* temp = (struct MinHeapNode*)malloc(
		sizeof(struct MinHeapNode));

	temp->left = temp->right = NULL;
	temp->data = data;
	temp->freq = freq;

	return temp;
}

// A utility function to create
// a min heap of given capacity
struct MinHeap* createMinHeap(unsigned capacity)

{

	struct MinHeap* minHeap
		= (struct MinHeap*)malloc(sizeof(struct MinHeap));

	// current size is 0
	minHeap->size = 0;

	minHeap->capacity = capacity;

	minHeap->array = (struct MinHeapNode**)malloc(
		minHeap->capacity * sizeof(struct MinHeapNode*));
	return minHeap;
}

// A utility function to
// swap two min heap nodes
void swapMinHeapNode(struct MinHeapNode** a,
					struct MinHeapNode** b)

{

	struct MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}

// The standard minHeapify function.
void minHeapify(struct MinHeap* minHeap, int idx)

{

	int smallest = idx;
	int left = 2 * idx + 1;
	int right = 2 * idx + 2;

	if (left < minHeap->size
		&& minHeap->array[left]->freq
			< minHeap->array[smallest]->freq)
		smallest = left;

	if (right < minHeap->size
		&& minHeap->array[right]->freq
			< minHeap->array[smallest]->freq)
		smallest = right;

	if (smallest != idx) {
		swapMinHeapNode(&minHeap->array[smallest],
						&minHeap->array[idx]);
		minHeapify(minHeap, smallest);
	}
}

// A utility function to check
// if size of heap is 1 or not
int isSizeOne(struct MinHeap* minHeap)
{

	return (minHeap->size == 1);
}

// A standard function to extract
// minimum value node from heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap)

{

	struct MinHeapNode* temp = minHeap->array[0];
	minHeap->array[0] = minHeap->array[minHeap->size - 1];

	--minHeap->size;
	minHeapify(minHeap, 0);

	return temp;
}

// A utility function to insert
// a new node to Min Heap
void insertMinHeap(struct MinHeap* minHeap,
				struct MinHeapNode* minHeapNode)

{

	++minHeap->size;
	int i = minHeap->size - 1;

	while (i
		&& minHeapNode->freq
				< minHeap->array[(i - 1) / 2]->freq) {

		minHeap->array[i] = minHeap->array[(i - 1) / 2];
		i = (i - 1) / 2;
	}

	minHeap->array[i] = minHeapNode;
}

// A standard function to build min heap
void buildMinHeap(struct MinHeap* minHeap)

{

	int n = minHeap->size - 1;
	int i;

	for (i = (n - 1) / 2; i >= 0; --i)
		minHeapify(minHeap, i);
}

// A utility function to print an array of size n
void printArr(int arr[], int n, L* h, char f, int z)
{
	int i,j;
	for (i = 0; i < n; ++i)
		printf("%d", arr[i]);
	
	for (i = 0; i < z; ++i){
		if(f==h[i].letra){
			for (j = 0;  j< n; ++j)
				h[i].x[j]=arr[j]+'0';
		}
		
	}
	printf("\n");
}

// Utility function to check if this node is leaf
int isLeaf(struct MinHeapNode* root)

{

	return !(root->left) && !(root->right);
}

// Creates a min heap of capacity
// equal to size and inserts all character of
// data[] in min heap. Initially size of
// min heap is equal to capacity
struct MinHeap* createAndBuildMinHeap(char data[],
									int freq[], int size)

{

	struct MinHeap* minHeap = createMinHeap(size);
int i;
	for (i = 0; i < size; ++i)
		minHeap->array[i] = newNode(data[i], freq[i]);

	minHeap->size = size;
	buildMinHeap(minHeap);

	return minHeap;
}

// The main function that builds Huffman tree
struct MinHeapNode* buildHuffmanTree(char data[],
									int freq[], int size)

{
	struct MinHeapNode *left, *right, *top;

	// Step 1: Create a min heap of capacity
	// equal to size. Initially, there are
	// modes equal to size.
	struct MinHeap* minHeap
		= createAndBuildMinHeap(data, freq, size);

	// Iterate while size of heap doesn't become 1
	while (!isSizeOne(minHeap)) {

		// Step 2: Extract the two minimum
		// freq items from min heap
		left = extractMin(minHeap);
		right = extractMin(minHeap);

		// Step 3: Create a new internal
		// node with frequency equal to the
		// sum of the two nodes frequencies.
		// Make the two extracted node as
		// left and right children of this new node.
		// Add this node to the min heap
		// '$' is a special value for internal nodes, not
		// used
		top = newNode('$', left->freq + right->freq);

		top->left = left;
		top->right = right;

		insertMinHeap(minHeap, top);
	}

	// Step 4: The remaining node is the
	// root node and the tree is complete.
	return extractMin(minHeap);
}

// Prints huffman codes from the root of Huffman Tree.
// It uses arr[] to store codes
void printCodes(struct MinHeapNode* root, int arr[],
				int top, L* h, int z)

{

	// Assign 0 to left edge and recur
	if (root->left) {

		arr[top] = 0;
		printCodes(root->left, arr, top + 1,h,z);
	}

	// Assign 1 to right edge and recur
	if (root->right) {

		arr[top] = 1;
		printCodes(root->right, arr, top + 1,h,z);
	}

	// If this is a leaf node, then
	// it contains one of the input
	// characters, print the character
	// and its code from arr[]
	if (isLeaf(root)) {

		printf("%c: ", root->data);
		printArr(arr, top,h,root->data,z);
	}
}

// The main function that builds a
// Huffman Tree and print codes by traversing
// the built Huffman Tree
void HuffmanCodes(char data[], int freq[], int size, L* h)

{
	// Construct Huffman Tree
	struct MinHeapNode* root
		= buildHuffmanTree(data, freq, size);

	// Print Huffman codes using
	// the Huffman tree built above
	int arr[MAX_TREE_HT], top = 0;

	printCodes(root, arr, top, h, size);
}



int main() {
	
	int i,j;
	
	//Se crea y guarda la cadena
    char cadena[100];
    printf("Ingrese una cadena:");
    fgets(cadena, sizeof(cadena), stdin);
    
    //Obtenemos la longitud de la cadena y la cantidad de caracteres unicos
	int longitud = strlen(cadena);
    int d = (cUnicos(cadena));
    
    //Creamos el arreglo y llamamos un metodo que contara cuantas veces se repite un caracter
	L h[d];
	contarCaracteres(cadena,h);
    
    //Se crean los arreglos que almacenaran los caracteres y la frecuencia de los mismos
	char arr[d];
	int freq[d];
	for (i = 0; i < d; i++) {
		arr[i]=h[i].letra;
		freq[i]=h[i].val;
	}
	
	//Se llama la funcion de Huffman
	HuffmanCodes(arr, freq, d,h);
	
	//Imprimimos la cadena ya codificada
	for (i = 0; i < longitud-1; i++) {
		for (j = 0; j < d; j++) {
			if(h[j].letra==cadena[i])
			printf("%s ",h[j].x);
		}
	}
	
    return 0;
}
