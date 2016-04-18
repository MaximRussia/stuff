#include <iostream>
#include <stack>

struct leaf {
    public:
        int value;
        leaf* right;
        leaf* left;
        leaf* neighbor;

        leaf(int v, leaf* r, leaf* l) :
            value(v), right(r), left(l), neighbor(nullptr) {};
};

void find_neighbors(leaf* node, std::stack<leaf*> & stack)
{
    if (node == nullptr) {
        return;
    };

    if (!stack.empty()) {
        node->neighbor = stack.top();
        stack.pop();
    };

    find_neighbors(node->right, stack);
    find_neighbors(node->left, stack);
    stack.push(node);
}

void show_leaf(leaf* node)
{
	if (node == nullptr) {
		return;
	};

	std::cout << "Node: " << node->value << " neighbor: " << (node->neighbor != nullptr ? node->neighbor->value : 0) << std::endl;

	show_leaf(node->right);
	show_leaf(node->left);
}

int main()
{
	leaf* tree0 = new leaf(1, nullptr, nullptr);

	leaf* tree1 =
		new leaf(
			1,
			new leaf(3, nullptr, nullptr),
			new leaf(2, nullptr, nullptr)
		);

	leaf* tree2 =
		new leaf(
			1,
			new leaf(
				3,
				new leaf(7, nullptr, nullptr),
				new leaf(6, nullptr, nullptr)
			),
			new leaf(
				2,
				nullptr,
				new leaf(4, nullptr, nullptr)
			)
		);

	std::stack<leaf*> stack0;
	find_neighbors(tree0, stack0);
	std::cout << "Tree #0" << std::endl;
	std::cout << "(1)" << std::endl;
	show_leaf(tree0);
	std::cout << std::endl;

	std::stack<leaf*> stack1;
	find_neighbors(tree1, stack1);
	std::cout << "Tree #1" << std::endl;
	std::cout << "   (1)" << std::endl;
	std::cout << "  /   \\" << std::endl;
	std::cout << "(2)   (3)" << std::endl;
	show_leaf(tree1);
	std::cout << std::endl;

	std::stack<leaf*> stack2;
	find_neighbors(tree2, stack2);
	std::cout << "Tree #2" << std::endl;
	std::cout << "    (1)" << std::endl;
	std::cout << "    / \\" << std::endl;
	std::cout << "  (2)  (3)" << std::endl;
	std::cout << "  /    / \\" << std::endl;
	std::cout << "(4)  (6)  (7)" << std::endl;
	show_leaf(tree2);
	std::cout << std::endl;

	return 0;
}
