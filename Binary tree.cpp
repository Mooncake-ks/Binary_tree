#include <iostream>


class Binary_tree
{
public:
	struct Node
	{
		int m_data;
		Node* m_left{ nullptr };
		Node* m_right{ nullptr };
		Node(const int& data, Node* left = nullptr, Node* right = nullptr);
	};
	Binary_tree();
	~Binary_tree();
	void add_node(const int& data);
	void remove(const int& data);
	void inorder_print() const;
	Node* search(const int& data);

private:
	
	Node* m_root{nullptr};
	void add_node(const int& data, Node* other_node);
	Node* remove(const int& data,Node* other_node);
	Node* search(const int& data, Node* other_node) const;
	void destroy_tree(Node* other_node);
	void inorder_print(Node* other_node) const;
};



int main()
{
	Binary_tree a;
	a.add_node(5);
	a.add_node(2);
	a.add_node(10);
	a.add_node(12);
	a.add_node(3);
	a.add_node(1);
	a.add_node(7);
	a.add_node(11);
	a.inorder_print();

	a.remove(1);
	a.inorder_print();
	system("pause");
	return 0;
}

//Конструктор узлов по умолчанию
Binary_tree::Node::Node(const int& data, Node* left, Node* right) :m_data{ data }, m_left{ left }, m_right{right} {}

//Конструктор дерева
Binary_tree::Binary_tree() : m_root{nullptr} {}

Binary_tree::~Binary_tree()
{
	destroy_tree(m_root);
}

//Добавление элемента в древо
void Binary_tree::add_node(const int& data)
{
	//Если дерево пустое добавляем  корень
	if (!m_root)
	{
		m_root = new Node(data);
	}
	else
	{
		add_node(data, m_root);
	}
}

//Удаление узла по данным
void Binary_tree::remove(const int& data)
{
	remove(data, m_root);
}

void Binary_tree::inorder_print() const 
{
	inorder_print(m_root);
	std::cout << "\n";
}

//Поиск узла по данным
Binary_tree::Node* Binary_tree::search(const int& data)
{
	return search(data, m_root);
}

//Рекурсивный поиск узла для добавления данных 
void Binary_tree::add_node(const int& data, Node* other_node)
{
	//Дублирование данных Выбрасывает исключение
	if (data == other_node->m_data) { throw "Data repetition"; };
	
	if (data < other_node->m_data)
	{
		if (other_node->m_left != nullptr)
		{
			add_node(data, other_node->m_left);
		}
		else
		{
			other_node->m_left = new Node(data);
		}
	}
	else if(data > other_node->m_data)
	{
		if (other_node->m_right != nullptr)
		{
			add_node(data, other_node->m_right);
		}
		else
		{
			other_node->m_right = new Node(data);
		}
	}
}

Binary_tree::Node* Binary_tree::remove(const int& data, Node* other_node)
{
	//Поиск нужного узла
	if (!other_node) { delete other_node; }
	else if (data < other_node->m_data)
	{
		other_node->m_left= remove(data, other_node->m_left);
	}
	else if (data > other_node->m_data)
	{
		other_node->m_right= remove(data, other_node->m_right);
	}
	//Найден нужный узел 
	else
	{
		//Если у узла нету детей
		if (other_node->m_left == nullptr && other_node->m_right == nullptr)
		{
			delete other_node;
			other_node = nullptr;
			return other_node;
		}
		//Если у узлаесть один ребёнок 
		else if (other_node->m_left == nullptr)
		{
			Node* temp = other_node;
			other_node = other_node->m_right;
			delete temp;
			return other_node;
		}
		else if (other_node->m_right == nullptr)
		{
			Node* temp = other_node;
			other_node = other_node->m_left;
			delete temp;
			return other_node;
		}
		//Если у узла два ребенка
		else
		{
			Node* temp = other_node->m_right;
			while (temp->m_left != nullptr) { temp = temp->m_left; }
			other_node->m_data = temp->m_data;
			other_node->m_right = remove(temp->m_data, other_node->m_right);
		}

	}
	return other_node;
}

 

Binary_tree::Node* Binary_tree::search(const int& data, Node* other_node)const 
{
	if (other_node!=nullptr)
	{
		if (data==other_node->m_data)
		{
			return other_node;
		}
		if (data < other_node->m_data)
		{
			search(data,other_node->m_left);
		}
		else if (data > other_node->m_data)
		{
			search(data, other_node->m_right);
		}
	}
	else
	{
		return nullptr;
	}
}

void Binary_tree::destroy_tree(Node* other_node)
{
	if (other_node != NULL) {
		destroy_tree(other_node->m_left);
		destroy_tree(other_node->m_right);
		delete other_node;
	}
}

void Binary_tree::inorder_print(Node* other_node)const 
{
	if (other_node)
	{
		inorder_print(other_node->m_left);
		std::cout << other_node->m_data << " ";
		inorder_print(other_node->m_right);
	}
}
