#include "ArgumentManager.h"
#include "List.h"

int main(int argc, char** argv)
{
	ArgumentManager am(argc, argv);
	string inputFile = am.get("input");
	string outputFile = am.get("output");

	List words;
	words.makeList(inputFile);
	Node* h = words.getHead();
	for (Node* cur = h; cur != nullptr; cur = cur->next)
		cout << cur->word << " ";


	if (words.length() > 0)
		words.output(outputFile);

}