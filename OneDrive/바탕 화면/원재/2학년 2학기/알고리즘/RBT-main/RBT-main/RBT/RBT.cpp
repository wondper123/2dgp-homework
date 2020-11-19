#define _CRT_SECURE_NO_WARNINGS
#define BLACK 0
#define RED 1
#include <iostream>
#include<queue>
#include<cmath>
using namespace std;

class Node
{
public:
	int key;

	bool Color; // BLACK : 0, RED : 1

	Node* Parent;

	Node* Left;
	Node* Right;
};

//A(왼쪽), B(오른쪽) 중에서 B가 root가 됨.(기존엔 A가 root)
void Left_Rotate(Node*& ROOT, Node* pivot, Node* NIL)	//ROOT는 최상단, pivot은 A, NIL은 최하단
{
	if (pivot->Right == NIL || pivot == NIL)		//A의 오른쪽(=B)이 NIL이거나 A가 NIL이면 
	{
		return;
	}

	Node* tmp = pivot->Right;							//트리회전 ppt의 left Rotation의 B(=pivot->Right)를 tmp에 저장

	pivot->Right = pivot->Right->Left;				//pivot은 A, A의 오른쪽 노드를 B의 왼쪽노드(=베타)로 변환

	if (NIL != pivot->Right)									//베타(바뀐 A의 오른쪽 노드)가 NIL이 아니면
	{
		pivot->Right->Parent = pivot;					//베타의 부모를 B로 연결
	}

	tmp->Left = pivot;											//tmp는 B, B의 왼쪽에 pivot(=A)를 연결, B가 root가 되고 A가 B의 밑층 pivot이 되도록
	Node* ptmp = pivot;										//ptmp에 A(=pivot)를 대입
	tmp->Parent = pivot->Parent;						//B(=tmp)의 부모에 A(pivot)의 기존 부모를 연결 -> 기존 A는 root였지만 이젠 B가 root가 되므로.

	if (pivot->Parent != NULL)							//A의 부모가 NULL이 아니면(기존 root가 제일 최상단이 아니었다면)
	{
		if (pivot->Parent->Left == pivot)				//A의 부모의 left가 A였으면
		{
			pivot->Parent->Left = tmp;					//A 부모의 left를 B에 연결
		}
		else
		{
			pivot->Parent->Right = tmp;				//A의 부모의 right가 A였으면 A부모의 right를 B에 연결
		}
	}

	pivot->Parent = tmp;										//A의 부모를 B로 만듦

	if (ROOT == ptmp)											//인자로 받은 ROOT가 A와 같다면
	{
		ROOT = tmp;												//ROOT를 B로 바꿔준다.(왜냐하면 A가 최상단 ROOT였을때 left_rotate를 해서 B가 최상단으로 바뀌었으므로.)
	}
}
//A(왼쪽), B(오른쪽) 중에서 A가 root가 됨.(기존엔 B가 root)
void Right_Rotate(Node*& ROOT, Node* pivot, Node* NIL)//ROOT는 최상단, pivot은 B, NIL은 최하단
{
	if (pivot->Left == NIL || pivot == NIL)		//B(=pivot)의 왼쪽이 NIL이거나 B가 NIL이면
	{
		return;
	}

	Node* tmp = pivot->Left;								//tmp는 B(=pivot)의 왼쪽노드(=A(pivot->Left))

	pivot->Left = pivot->Left->Right;				//B의 왼쪽에 B왼쪽(=A)의 오른쪽 노드를 연결
	
	if (pivot->Left != NIL)										//A(=pivot->Left)가 NIL이 아니면
	{
		pivot->Left->Parent = pivot;						//A의 부모는 B
	}

	tmp->Right = pivot;											//B(=pivot)를 A의 오른쪽에 연결 -> A가 B보다 윗층에 위치하게 됨
	Node* ptmp = pivot;										//ptmp에 B를 대입
	tmp->Parent = pivot->Parent;						//A의 부모를 기존 B의 부모로 연결

	if (pivot->Parent != NULL)							//B의 부모가 NULL이 아니었다면
	{
		if (pivot->Parent->Left == pivot)				//기존 B가 부모의 왼쪽노드였으면
		{
			pivot->Parent->Left = tmp;					//A를 기존B부모의 왼쪽노드로 연결
		}
		else
		{
			pivot->Parent->Right = tmp;				//기존 B가 부모의 오른쪽 노드였으면 A를 기존B부모의 오른쪽 노드로 연결
		}
	}

	tmp->Right->Parent = tmp;							//A의 오른쪽(=B)의 부모를 A로 만듦.

	if (ROOT == ptmp)											//기존 최상단 ROOT가 B였다면
	{	
		ROOT = tmp;												//최상단에 A를 위치시킴.
	}
}
//1.루트는 블랙이다, 2.모든 리프는 블랙이다, 3.노드가 레드이면 그 자식은 반드시 블랙이다, 4.루트 노드에서 임의의 리프 노드에 이르는 경로에서 만나는 블랙 노드의 수는 모두 같다.
void Check_Tree(Node*& ROOT, Node* node, Node* NIL, bool PrevColor, int level) //ROOT는 최상단, node는 삽입노드, NIL은 NIL, PrevColor는 부모노드의 색상, level은 위부터 아래로의 층수
{
	if (level == 0)
	{
		if (node->Color == BLACK)
		{
			if(node->Left != NIL)
				Check_Tree(ROOT, node->Left, NIL, BLACK, level + 1);//다음레벨 왼쪽으로
			if (node->Right != NIL)
				Check_Tree(ROOT, node->Right, NIL, BLACK, level + 1);//다음레벨 오른쪽으로
		}
		else
		{
			cout << "규칙 위반 발생! " << level << "번 층의 " << node->key << "의 값을 가진 노드" << endl;
			cout << "사유 : 루트 노드가 레드" << endl;
			node->Color = BLACK;
		}
	}
	else
	{
		if (node->Color == RED)
		{
			if (PrevColor == RED)
			{
				cout << "규칙 위반 발생! " << level << "번 층의 " << node->key << "의 값을 가진 노드" << endl;
				cout << "사유 : 부모가 레드인데 자식도 레드" << endl;

				//삼촌 노드 체크

				//부모가 왼쪽 노드일때
				if (node->Parent->Parent->Left == node->Parent)
				{
					//삼촌 노드가 블랙/NIL일때 회전
					if (node->Parent->Parent->Right->Color == BLACK)
					{
						//삽입한 노드가	부모의 오른쪽 자식인 경우
						if (node == node->Parent->Right)
						{
							Left_Rotate(ROOT, node->Parent, NIL);
							node->Parent->Color = RED;
							node->Color  = BLACK;
							Right_Rotate(ROOT, node->Parent, NIL);
						}
						//삽입한 노드가 부모의 왼쪽 자식인 경우
						else if (node == node->Parent->Left)
						{
							node->Parent->Parent->Color = RED;
							node->Parent->Color = BLACK;
							Right_Rotate(ROOT, node->Parent->Parent, NIL);
						}
					}
					//삼촌 노드가 레드일때 색상변경
					else if (node->Parent->Parent->Right->Color == RED)
					{
						//조부모를 레드, 부모를 블랙, 삼촌을 블랙으로
						node->Parent->Color = BLACK;

						//증조부모가 NIL이면 조부모는 루트 노드
						if (node->Parent->Parent->Parent == NIL)
						{
							//루트 노드는 항상 블랙
							node->Parent->Parent->Color = BLACK;
						}
						else
						{
							//조부모가 루트노드가 아닐경우
							node->Parent->Parent->Color = RED;

							//재귀적인 경우 한번 더 체크
							Check_Tree(ROOT, ROOT, NIL, BLACK, 0);
						}

						node->Parent->Parent->Right->Color = BLACK;
					}
				}

				//부모가 오른쪽 노드일때
				else if (node->Parent->Parent->Right == node->Parent)
				{
					//삼촌 노드가 블랙/NIL일때 회전
					if (node->Parent->Parent->Left->Color == BLACK)
					{
						//삽입한 노드가	부모의 오른쪽 자식인 경우
						if (node == node->Parent->Right)
						{
							Left_Rotate(ROOT, node->Parent, NIL);
							node->Parent->Color = RED;
							node->Color = BLACK;
							Right_Rotate(ROOT, node->Parent, NIL);
						}
						//삽입한 노드가 부모의 왼쪽 자식인 경우
						else if (node == node->Parent->Left)
						{
							node->Parent->Parent->Color = RED;
							node->Parent->Color = BLACK;
							Right_Rotate(ROOT, node->Parent, NIL);
						}
					}
					//삼촌 노드가 레드일때 색상변경
					else if (node->Parent->Parent->Left->Color == RED)
					{
						//조부모를 레드, 부모를 블랙, 삼촌을 블랙으로
						node->Parent->Color = BLACK;

						//증조부모가 NIL이면 조부모는 루트 노드
						if (node->Parent->Parent->Parent == NIL)
						{
							//루트 노드는 항상 블랙
							node->Parent->Parent->Color = BLACK;
						}
						else
						{
							//조부모가 루트노드가 아닐경우
							node->Parent->Parent->Color = RED;

							//재귀적인 경우 한번 더 체크
							Check_Tree(ROOT, ROOT, NIL, BLACK, 0);
						}

						node->Parent->Parent->Left->Color = BLACK;
					}
				}

			}
		}

		if (node->Left != NIL)
			Check_Tree(ROOT, node->Left, NIL, node->Color, level + 1);
		if (node->Right != NIL)
			Check_Tree(ROOT, node->Right, NIL, node->Color, level + 1);
	}
}


void Init_BT(Node*& root, Node*& NIL, int key)
{
	NIL = (Node*)malloc(sizeof(Node));
	NIL->Parent = NULL;
	NIL->Left = NULL;
	NIL->Right = NULL;
	NIL->Color = BLACK;

	root = (Node*)malloc(sizeof(Node));
	root->Parent = NIL;
	root->key = key;
	root->Left = NIL;
	root->Right = NIL;
	root->Color = BLACK;
}

void Insert_BT(Node*& root, Node*& NIL, int key, int level)
{
	if (root->key > key)
	{
		if (root->Left == NIL)
		{
			Node* newNode = (Node*)malloc(sizeof(Node));
			newNode->key = key;
			newNode->Left = NIL;
			newNode->Right = NIL;
			newNode->Color = RED;
			newNode->Parent = root;
			root->Left = newNode;
		}
		else
		{
			Insert_BT(root->Left, NIL, key, level + 1);
		}
	}
	else if (root->key < key)
	{
		if (root->Right == NIL)
		{
			Node* newNode = (Node*)malloc(sizeof(Node));
			newNode->key = key;
			newNode->Left = NIL;
			newNode->Right = NIL;
			newNode->Color = RED;
			newNode->Parent = root;
			root->Right = newNode;
		}
		else
		{
			Insert_BT(root->Right, NIL, key, level + 1);
		}
	}
}

void Delete_BT(Node* root, int key)
{
	Node* tmp = NULL;

	if (root == NULL)
	{
		return;
	}
	else if (root->key > key)
	{
		Delete_BT(root->Left, key);
	}
	else if (root->key < key)
	{
		Delete_BT(root->Right, key);
	}
	else
	{
		if (root->Right != NULL)
		{
			for (Node* p = root->Right; ; p = p->Left)
			{
				if (p->Left == NULL)
				{
					tmp = p;
					break;
				}
			}
			root->key = tmp->key;

			for (Node* p = root->Right; ; p = p->Left)
			{
				if (p->Left == tmp)
				{
					p->Left = NULL;
					free(tmp);
					return;
				}

				else if (p->Left == NULL)
				{
					root->Right = NULL;
					free(tmp);
					return;
				}
			}
		}
		else if (root->Left != NULL)
		{
			tmp = root;
			root = root->Left;
			free(tmp);
			return;
		}
		else if (root->Left == NULL && root->Right == NULL)
		{
			tmp = root;
			root = NULL;
			free(tmp);
			return;
		}
	}
}
void Print_RBT(Node* node, int max_level, int my_level, int cnt)//색깔 블랙, 레드 나눠서 출력
{
	
	if (node->Color == BLACK)
	{
		for (int i = 0; i < max_level - my_level; ++i)//레벨 별 간격 띄우기
			cout << "       ";//spacebar 5번
		if ((my_level != max_level && cnt == pow(2, my_level + 1) - my_level)||my_level==0)//가운데 정렬 비슷하게 하기(좀 어색하게 구현됨, 완벽하진 않음)
			for (int i = 0; i < max_level - my_level; ++i)
				cout << "  ";
		printf("○%d", node->key);
	}
	else
	{
		for (int i = 0; i < max_level - my_level; ++i)//레벨 별 간격 띄우기
			cout << "       ";//spacebar 5번
		if ((my_level != max_level && cnt == pow(2, my_level + 1) - my_level) || my_level == 0)//가운데 정렬 비슷하게 하기(좀 어색하게 구현됨, 완벽하진 않음)
			for (int i = 0; i < pow(2, max_level - my_level); ++i)
				cout << "  ";
		printf("●%d", node->key);
	}
	if (cnt == pow(2, my_level + 1) - 1)//줄바꿈(층바꿈)
		cout << endl;
}

int tree_size(Node* ROOT, Node* NIL, int size)//ROOT부터 맨 아래까지 탐방하며 총 몇개의 Node가 있는지 세는 함수
{
	if (ROOT->Left == NIL && ROOT->Right == NIL)
		return size;
	else if (ROOT->Left != NIL && ROOT->Right != NIL)
		return size + tree_size(ROOT->Right, NIL, size) + tree_size(ROOT->Left, NIL, size);
	else if (ROOT->Left == NIL)
		return size + tree_size(ROOT->Right, NIL, size);
	else if (ROOT->Right == NIL)
		return size + tree_size(ROOT->Left, NIL, size);
}
int max_level_counter(int size)//총 몇 개의 층이 있는지 계산
{
	int max_level = 0;
	while (size > 0)
	{
		++max_level;
		size /= 2;
	}
	return max_level;
}
int my_level_counter(int cnt)//현재 자신의 층이 몇 층인지 계산
{
	int level =1;
	while (!(cnt < pow(2,level)))
		++level;
	return level-1;
}
//큐를 이용해서 레벨 순서 순회를 하며 출력
void RBT_queue_Print(queue<Node*>q, Node* NIL, Node* ROOT)//Dequeue할 때 Print_RBT
{
	q.push(ROOT);
	int my_level = 0;//시작 층은 0층
	int cnt = 1;//현재 몇번째 노드인지 카운트
	int max_level = max_level_counter(tree_size(ROOT, NIL, 1));// 총 몇 층인지 계산
	cout << "○가 블랙, ●가 레드" << endl;
	while (!q.empty())//큐가 빌 때까지 반복
	{
		Node* tmp = q.front();//큐의 제일 앞쪽(먼저 들어온 노드)
		my_level = my_level_counter(cnt);//내 현재 층 계산
		
		q.pop();//큐에써 빼기
		Print_RBT(tmp, max_level, my_level, cnt);//현재 자기 자신의 노드 출력 및 줄바꿈
		++cnt;

		if (tmp->Left!=NIL)
			q.push(tmp->Left);//왼쪽 노드 탐색 후 큐에 넣기
		if (tmp->Right!=NIL)
			q.push(tmp->Right);//오른쪽 노드 탐색 후 큐에 넣기
	}
	cout << endl;
	cout << "출력종료" << endl;
}

int main()
{
	Node* NIL = NULL;
	Node* ROOT = NULL;

	queue<Node*>queue;

	Init_BT(ROOT, NIL, 20);
	RBT_queue_Print(queue, NIL, ROOT);

	Insert_BT(ROOT, NIL, 15, 0);
	Check_Tree(ROOT, ROOT, NIL, BLACK, 0);
	RBT_queue_Print(queue, NIL, ROOT);

	Insert_BT(ROOT, NIL, 3, 0);
	Check_Tree(ROOT, ROOT, NIL, BLACK, 0);
	RBT_queue_Print(queue, NIL, ROOT);

	Insert_BT(ROOT, NIL, 12, 0);
	Check_Tree(ROOT, ROOT, NIL, BLACK, 0);
	RBT_queue_Print(queue, NIL, ROOT);

	Insert_BT(ROOT, NIL, 5, 0);
	Check_Tree(ROOT, ROOT, NIL, BLACK, 0);
	RBT_queue_Print(queue, NIL, ROOT);

	Insert_BT(ROOT, NIL, 11, 0);
	Check_Tree(ROOT, ROOT, NIL, BLACK, 0);
	RBT_queue_Print(queue, NIL, ROOT);

	Insert_BT(ROOT, NIL, 6, 0);
	Check_Tree(ROOT, ROOT, NIL, BLACK, 0);
	RBT_queue_Print(queue, NIL, ROOT);

	Insert_BT(ROOT, NIL, 40, 0);
	Check_Tree(ROOT, ROOT, NIL, BLACK, 0);
	RBT_queue_Print(queue, NIL, ROOT);

	Insert_BT(ROOT, NIL, 25, 0);
	Check_Tree(ROOT, ROOT, NIL, BLACK, 0);
	RBT_queue_Print(queue, NIL, ROOT);

	Insert_BT(ROOT, NIL, 18, 0);
	Check_Tree(ROOT, ROOT, NIL, BLACK, 0);
	RBT_queue_Print(queue, NIL, ROOT);
}