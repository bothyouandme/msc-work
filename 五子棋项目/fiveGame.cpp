/********************************************************
    //需要你们实现的：
    类内的两个函数
    Node* generateTree(int x, int y, int currentLayer, bool type);
    int DFS(Node*, int, int); //该函数进行剪枝，返回后的最大代价
    
    全局的函数countscore（因为不涉及类内的成员，所以不是成员函数
**********************************************************/
#include <iostream>
#include <vector> 
#include <queue>

#define INFI 1000000

using namespace std;
typedef struct Node
{
public:
    int alpha, beta;
    int x, y; //记录这一步下在哪个位置
    char currentChar;
    int notLeaf; //0 for leaf, 1 for Max, 2 for Min
    //每次操作加个vectorLen
    vector<Node*> pointers;
    Node(int a, int b, bool m, int X, int Y, char c):
        alpha(a), beta(b), notLeaf(m), x(X), y(Y), currentChar(c) {}
}Node;
class fiveGame
{
private:
    char player, pc;
    int len;
    bool whoFirst;
    int currentX;
    int currentY;
    int layerLimit; //这个参数控制了深度，请在constructor中自行调整
    vector<vector<char>> a;
    vector<vector<bool>> avaliable;
public:
    fiveGame(int, int);
    ~fiveGame();
    bool checkValid(string str);
    void MinMax();
    void print_board();
    void setAvaliable(int, int);
    
    int readAndCheck();
    int initailize();
    int checkResult(bool);
    int h(int x, int y);

    //需要实现的
    Node* generateTree(int x, int y, int currentLayer, bool type);
    int DFS(Node*, int, int); //该函数进行剪枝，返回后的最大代价
    
};
void fiveGame::setAvaliable(int x, int y) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++) {
            int tempy = y-2+j;
            int tempx = x-2+i;
            if (tempx < 0 || tempx >= len || tempy < 0 || tempy >= len)
                continue;
            else 
                avaliable[tempx][tempy] = true;
        }
}
fiveGame::fiveGame(int N, int first):len(N), whoFirst(first), 
currentX(0), currentY(0)
{
    vector<char> tempchar = vector<char>(len, ' ');
    a = vector<vector<char>>(len, tempchar);
    vector<bool> tempbool = vector<bool>(len, false);
    avaliable = vector<vector<bool>>(len, tempbool);
    layerLimit = 1;
    if (whoFirst) {
        player = 'x';
        pc = 'o';
        currentY = 5;
        currentX = 5;
    } else {
        player = 'o';
        pc = 'x';
        currentY = 4;
        currentX = 5;
    }
    a[5][5] = 'x';
    setAvaliable(5, 5);
    a[5][6] = 'x';
    setAvaliable(5, 6);
    a[6][5] = 'o';
    setAvaliable(6, 5);
    a[5][4] = 'o';
    setAvaliable(5, 4);
    initailize();
}
fiveGame::~fiveGame()
{
}
void fiveGame::print_board() {
    cout << "  ";
    for (int i = 0; i < len; i++) {
        
        if (i/10)
            cout << "-" << i << "-";
        else 
            cout << "--" << i << "-"; 
    }
    cout << "-";
    cout << endl;
    for (int i = 0; i < len; i++) {
        cout << i;
        if (!(i / 10))
            cout << " ";
        for (int j = 0; j < len; j++) 
            cout << "| " << a[i][j] << " ";
        cout << "|" << endl;
        cout << "  ";
        for (int j = 0; j < len; j++)
            cout << "----";
        cout << "-";
        cout << endl;
    }
}
int fiveGame::readAndCheck() {
    cout << "you are ";
    if (whoFirst)
        cout << "x" << endl;
    else 
        cout << "o" << endl;
    cout << "please enter your choice: \ne.g 1, 2\n";
    string tempstr;
    //cin.clear();
    getline(cin, tempstr); 
    return checkValid(tempstr);
}

bool fiveGame::checkValid(string str) {
    int m, n;
    // char tempS[] = str.c_str();
    //cout << "str: " << str << endl;
    sscanf(str.c_str(), "%d, %d", &m, &n);
    if (m < 0 || m >= len || n < 0 || n >= len)
        return false;
    //cout << m << "---" << n << endl;
    if (a[m][n] == ' ') {
        a[m][n] = player;
        currentX = m;
        currentY = n;
        setAvaliable(m, n);
        return true;
    } else {
        return false;
    }
}
//如何建立博弈树
//选定一个点，构造树
//对所有需要构造树的结点，递归调用
//遇到层数上限则返回
//这些函数接口大家按心情随意改都可
Node* fiveGame::generateTree(int x, int y, int currentLayer, bool type) {
    
}
int fiveGame::DFS(Node* father, int alpha, int beta) {

}
int countscore(vector<char> n, char turn)//正斜线、反斜线、横、竖，均转成一维数组来计算 
{
    
}


//维护表，每次只改动下了子的行列斜线，放在类里更合理，但懒得改了
int row[11][2];
int col[11][2];
int leftUP[11][2];
int leftDown[11][2];
int rightUP[11][2];
int rightDown[11][2];
int fiveGame::initailize() {
    //横排们 
	for(int i=0;i<len;++i)
	{
        vector<char> n;
        for(int j=0;j<len;++j)
            n.push_back(a[i][j]);
        row[i][0] = countscore(n,pc);
        //cout << "cost: " << row[i][0] << "|" << row[i][1] << endl;
        row[i][1] = countscore(n,player);
        // cout << "cost: " << row[i][1] << "|" << row[i][1] << endl;
        n.clear();
		
	}
	//竖排们
	for(int j=0;j<len;++j)
	{
        vector<char> n;
        for(int i=0;i<len;++i)
            n.push_back(a[i][j]);
        col[j][0] = countscore(n,pc);
        col[j][1] = countscore(n,player);
        n.clear();	
	} 
	//上半正斜线们 
	for(int i=0;i<len;++i)
	{
        int tx,ty;
        vector<char> n;
        for(tx=i,ty=0;tx<len&&ty<len;++tx,++ty)
            n.push_back(a[ty][tx]);
        leftUP[i][0] = countscore(n,pc);
        leftUP[i][1] = countscore(n,player);
        n.clear();
	} 
	//下半正斜线们
	for(int j=1;j<len;++j)
	{
		int x,y;
		vector<char> n;
		for(x=0,y=j;y<len&&x<len;++x,++y)
			n.push_back(a[y][x]);
	 	leftDown[j][0]=countscore(n,pc);
		leftDown[j][1]=countscore(n,player);
		n.clear();
	} 
	//上半反斜线们
	for(int i=0;i<len;++i)
	{
		vector<char> n;
		int x,y;
		for(y=i,x=0;y>=0&&x<len;--y,++x)
			n.push_back(a[y][x]);
		rightUP[i][0]=countscore(n,pc);
		rightUP[i][1]=countscore(n,player);
		n.clear();
	} 
	//下半反斜线们
	for(int j=1;j<len;++j)
	{
		vector<char> n;
		int x,y;
		for(y=j,x=len-1;y<len&&x>=0;++y,--x)
			n.push_back(a[x][y]);
        rightDown[j][0]=countscore(n,pc);
		rightDown[j][1]=countscore(n,player);
		n.clear();
	} 
}
//用于评估整个局面的分数
int fiveGame::h(int x, int y) {
    int scorecomputer=0;
	int scorehuman=0;
	//横排们 
	for(int i=0;i<len;++i)
	{
        if (i == x) {
            vector<char> n;
            for(int j=0;j<len;++j)
                n.push_back(a[i][j]);
            row[i][0] = countscore(n,pc);
            row[i][1] = countscore(n,player);
            n.clear();
        }
		scorecomputer+=row[i][0];
		scorehuman+=row[i][1];
	}
	//竖排们
	for(int j=0;j<len;++j)
	{
        if (j == y) {
            vector<char> n;
            for(int i=0;i<len;++i)
                n.push_back(a[i][j]);
            col[j][0] = countscore(n,pc);
            col[j][1] = countscore(n,player);
            n.clear();
        }
		scorecomputer+=col[j][0];
		scorehuman+=col[j][1];
	} 
	//上半正斜线们 
	for(int i=0;i<len;++i)
	{
        if (y-x == i) {
            int tx,ty;
            vector<char> n;
            for(tx=i,ty=0;tx<len&&ty<len;++tx,++ty)
                n.push_back(a[ty][tx]);
            leftUP[i][0] = countscore(n,pc);
            leftUP[i][1] = countscore(n,player);
            n.clear();
        }
		scorecomputer+=leftUP[i][0];
        scorehuman+=leftUP[i][1];
	} 
	//下半正斜线们
	for(int j=1;j<len;++j)
	{
        if (x-y == j) {
            int tx,ty;
            vector<char> n;
            for(tx=0,ty=j;tx<len&&ty<len;++tx,++ty)
                n.push_back(a[ty][tx]);
            leftDown[j][0] = countscore(n,pc);
            leftDown[j][1] = countscore(n,player);
            n.clear();
        }
		scorecomputer+=leftDown[j][0];
        scorehuman+=leftDown[j][1];
	} 
	//上半反斜线们
	for(int i=0;i<len;++i)
	{
        if (x-y == i) {
            int tx,ty;
            vector<char> n;
            for(tx=0,ty=i;tx<len&&ty>=0;++tx,--ty)
                n.push_back(a[ty][tx]);
            rightUP[i][0] = countscore(n,pc);
            rightUP[i][1] = countscore(n,player);
            n.clear();
        }
		scorecomputer+=rightUP[i][0];
        scorehuman+=rightUP[i][1];
	} 
	//下半反斜线们
	for(int j=0;j<len;++j)
	{
        if (y-x == j) {
            int tx,ty;
            vector<char> n;
            for(tx=len-1,ty=j;tx>=0&&ty<len;++ty,--tx)
                n.push_back(a[ty][tx]);
            rightDown[j][0] = countscore(n,pc);
            rightDown[j][1] = countscore(n,player);
            n.clear();
        }
		scorecomputer+=rightDown[j][0];
        scorehuman+=rightDown[j][1];
	}
    // cout << x << ", " << y << ", " << scorecomputer << ", " << scorehuman << endl;
	return scorecomputer-scorehuman;
}
void fiveGame::MinMax() {
    //true对应MAX枝，看alpha，反之MIN枝，看beta
    Node* father = generateTree(currentX, currentY, 0, true);
    int biggest = DFS(father, -1*INFI, INFI);//该函数返回了剪枝后的最大代价
    a[father->x][father->y] = player;
    int newx = 0;
    int newy = 0;
    for (auto p : father->pointers) {
        //cout << "----" << p->x << ", " << p->y << ": " << p->alpha << endl;
        if (p->alpha == biggest) {
            //biggest = p->alpha;
            newx = p->x;
            newy = p->y;
        }
    }

    a[newx][newy] = pc;
    setAvaliable(newx, newy);
    currentX = newx;
    currentY = newy;
}
//检查游戏是否结束，有否5子连珠
int fiveGame::checkResult(bool currentPlayer) {
    // char currentSymbol = (currentPlayer == whoFirst) ? player : pc;
    char currentSymbol = a[currentX][currentY];
    if (currentSymbol == ' ') 
        return 0;
    // 行
    int count = 0;
    for (int i = 1; i <= 4; i++) {
        if (currentX-i >= 0 && a[currentX-i][currentY] == currentSymbol)
            count++;
        else break;
    }
    for (int i = 1; i <= 4; i++) {
        if (currentX+i < len && a[currentX+i][currentY] == currentSymbol)
            count++;
        else break;
    }
    if (count >= 4)//算上自己是5
        return 1;
    // 列
    count = 0;
    for (int i = 1; i <= 4; i++) {
        if (currentY-i >= 0 && a[currentX][currentY-i] == currentSymbol)
            count++;
        else break;
    }
    for (int i = 1; i <= 4; i++) {
        if (currentY+i < len && a[currentX][currentY+i] == currentSymbol)
            count++;
        else break;
    }
    if (count >= 4)
        return 1;

    // 左上对角线
    count = 0;
    for (int i = 1; i <= 4; i++) {
        if (currentX-i >= 0 && currentY-i >= 0 && a[currentX-i][currentY-i] == currentSymbol)
            count++;
        else break;
    }
    for (int i = 1; i <= 4; i++) {
        if (currentX+i < len && currentY+i < len && a[currentX+i][currentY+i] == currentSymbol)
            count++;
        else break;
    }
    if (count >= 4)
        return 1;
    // 右上对角线
    count = 0;
    for (int i = 1; i <= 4; i++) {
        if (currentX+i < len && currentY-i >= 0 && a[currentX+i][currentY-i] == currentSymbol)
            count++;
        else break;
    }
    for (int i = 1; i <= 4; i++) {
        if (currentX-i >= 0 && currentY+i < len && a[currentX-i][currentY+i] == currentSymbol)
            count++;
        else break;
    }
    if (count >= 4)
        return 1;
        
    return 0;//平局略，可以通过双方子数判断
}

int main() {
    //initialize //it's said to be 15
    int len = 11;
    int whoFirst;
    string temp;
    //choose who first
    cout << "choose who play first, 0 for pc, 1 for human" << endl; 
    cin >> whoFirst;//read \n
    getline(cin, temp); 
    fiveGame Game(len, whoFirst);
    bool playerTurn = whoFirst;
    // 1 for someone wins, 2 for tie, 0 for no result
    int winner = 0;
    Game.print_board();
    while(1) {
        if (playerTurn) {
            if (!Game.readAndCheck()) {
                cout << "invalid input!" << endl;
                continue;
            }
        } else {
            //Game.MinMax();
            cout << "computer pass!" << endl;
        }

        Game.print_board();
        if (winner = Game.checkResult(playerTurn))
            break;
        playerTurn = ! playerTurn; 
    }
    Game.print_board();
    switch (winner)
    {
    case 1:
        if (playerTurn)
            cout << "player wins!" << endl;
        else
            cout << "pc wins!" << endl;
        break;
    case 2:
        cout << "tie!" << endl;
        break;
    default:
        break;
    }
    cout << "wait for any key..." << endl;
    cin >> temp;
}