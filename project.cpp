#include<bits/stdc++.h>
using namespace std;

class Location
{
    bool left,right,up,down,visit;
    int x,y;
    int prevX,prevY;
    Location* prev;
    bool start,final;
    char name;
    int cost;

    public:
    Location(bool left = false, bool right = false, bool up = false, bool down = false, char n = ' ', int cost = 0)
    : left(left), right(right), up(up), down(down), name(n), cost(cost)
    {
        start = false;
        final = false;
        prev = NULL;
        visit = false;
        x=0;
        y=0;
        prevX=0;
        prevY=0;
    }
    Location(const Location& L){
        name= L.name;
        visit =  L.visit;
        down = L.down;
        up = L.up;
        left= L.left;
        right = L.right;
        x = L.x;
        y = L.y;
        prevX= L.prevX;
        prevY= L.prevY;
        cost = L.cost;
        start = L.start;
        final = L.final;
        prev = L.prev;
    }

    void Setname(char n=' ') {name = n;}
    void Setvisit(bool v = true)
    {
        visit = v;
        if(this->getname() == ' ')
            this->Setname('.');
        }
        void Setdown(bool d = true) {down = d;}
        void Setup(bool t = true) {up = t;}
        void Setleft(bool l=true) {left = l;}
        void Setright(bool r = true) {right = r;}
        void SetX(int xx) {x = xx;}
        void SetY(int yy) {y = yy;}
        void SetprevX(int x) {prevX = x;}
        void SetprevY(int y) {prevY = y;}
        void Setstart(bool s = true) {start =s;}
        void Setfinal(bool g = true) {final =g;}
        void Setcost(int c) {cost=c;}
        void Setprev(Location *p) {prev = p;}


    Location* getprev() {return prev;}
    char getname() {return name;}
    bool getvisit() {return visit;}
    bool getdown() {return down;}
    bool getup() {return up;}
    bool getleft() {return left;}
    bool getright() {return right;}
    int getX() {return x;}
    int getY() {return y;}
    int getprevX() {return prevX;}
    int getprevY() {return prevY;}
    bool getfinal() {return final;}
    bool getstart() {return start;}
    int getcost() {return cost;}
};

class Map
{
    vector< vector<Location*> > MAP;
    int row,col;
    Location* start,final;
    public:
    Map(int r = 0, int c = 0)
    {
        row = r;
        col = c;
        start = NULL;
        final = NULL;

    }
    Map(Map &m)
    {
        MAP=m.MAP;
        row = m.row;
        col = m.col;
        start=m.start;
        final=m.final;
    }
    int getrow(){return row;}
    int getcol(){return col;}
    vector< vector<Location*> > getmap() {return MAP;}
    void line(vector<Location*> line);
    void setCoordinates();
    void setStart();
    void setFinal();
    void BFS();
    void DFS();
    void checkbd(Location* cur);
};

void Map ::line(vector<Location*> line)
{
    MAP.push_back(line);
    row+=1;
    col = line.size();
}

void Map::setCoordinates()
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            MAP[i][j]->SetX(i);
            MAP[i][j]->SetY(j);
        }
    }
}

void Map ::setStart()
{
    for(int i=0;i<row;++i)
    {
        for(int j=0;j<col;++j)
        {
            if(MAP[i][j]->getstart())
                start = MAP[i][j];
        }
    }
}
void Map ::setFinal()
{
    for(int i=0;i<row;++i)
    {
        for(int j=0;j<col;++j)
        {
            if(MAP[i][j]->getfinal())
                final = MAP[i][j];
        }
    }
}

void Map::checkbd(Location* final)
{
    stack<Location*> check;
    check.push(final);
    final = (final->getprev());

    if (final == NULL)
     cout << "NULL" << endl;

    while (final != NULL)
    {
         if (final->getname() == '.')
         {
             final->Setname('o');
         }
         check.push(final);
         final = (final->getprev());
    }
    cout<<"Path: ";
    while (!check.empty())
    {
         cout <<"(" << (check.top()->getX() + 1) << ", " << (check.top()->getY() + 1) << ") ";
         check.pop();
    }
    cout << endl << endl;
}

void Map :: DFS()
{
    Location* curr;
    stack<Location*> stk;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            MAP[i][j]->Setvisit(false);
            if (MAP[i][j] == start)
            {
                MAP[i][j]->Setvisit(true);
                stk.push(MAP[i][j]);
            }
        }
    }
    while (!stk.empty())
    {
        curr = stk.top();
        stk.pop();
        curr->Setvisit();
        if (curr->getfinal())
        {
            return checkbd(curr);
        }
        if (curr->getdown() == true and ((MAP[curr->getX() + 1][(curr->getY())])->getvisit() == false))
        {
            stk.push(MAP[curr->getX() + 1][((curr->getY()))]);
            MAP[curr->getX() + 1][(curr->getY())]->Setprev(curr);
        }
        if (curr->getright() == true and ((MAP[curr->getX()][(curr->getY() + 1)])->getvisit() == false))
        {
            stk.push(MAP[((curr->getX()))][(curr->getY() + 1)]);
            MAP[curr->getX()][(curr->getY() + 1)]->Setprev(curr);
        }
        if (curr->getleft() == true and ((MAP[curr->getX()][(curr->getY() - 1)])->getvisit() == false))
        {
            stk.push(MAP[((curr->getX()))][(curr->getY() - 1)]);
            MAP[curr->getX()][(curr->getY() - 1)]->Setprev(curr);
        }
        if (curr->getup() == true and ((MAP[curr->getX() - 1][(curr->getY())])->getvisit() == false))
        {
            stk.push(MAP[curr->getX() - 1][(curr->getY())]);
            MAP[curr->getX() - 1][(curr->getY())]->Setprev(curr);
        }
    }
    cout << "Sorry, this route is not possible using DFS\n";
}

void Map :: BFS()
{
    Location* curr;
    queue<Location*> q;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            MAP[i][j]->Setvisit(false);
            if (MAP[i][j] == start)
            {
                MAP[i][j]->Setvisit(true);
                q.push(MAP[i][j]);
            }
        }
    }
    while (!q.empty())
    {
        curr = q.front();
        q.pop();
        curr->Setvisit();
        if (curr->getfinal())
        {
            return checkbd(curr);
        }
        if (curr->getdown() == true and ((MAP[curr->getX() + 1][(curr->getY())])->getvisit() == false))
        {
            q.push(MAP[curr->getX() + 1][((curr->getY()))]);
            MAP[curr->getX() + 1][(curr->getY())]->Setprev(curr);
        }
        if (curr->getright() == true and ((MAP[curr->getX()][(curr->getY() + 1)])->getvisit() == false))
        {
            q.push(MAP[((curr->getX()))][(curr->getY() + 1)]);
            MAP[curr->getX()][(curr->getY() + 1)]->Setprev(curr);
        }
        if (curr->getleft() == true and ((MAP[curr->getX()][(curr->getY() - 1)])->getvisit() == false))
        {
            q.push(MAP[((curr->getX()))][(curr->getY() - 1)]);
            MAP[curr->getX()][(curr->getY() - 1)]->Setprev(curr);
        }
        if (curr->getup() == true and ((MAP[curr->getX() - 1][(curr->getY())])->getvisit() == false))
        {
            q.push(MAP[curr->getX() - 1][(curr->getY())]);
            MAP[curr->getX() - 1][(curr->getY())]->Setprev(curr);
        }
    }
    cout << "Sorry, this route is not possible using BFS\n";
}

bool LoadMap(Map &M)
{
        string fname;
        cout << "\nWhich map do you want to load?: ";
        cin.ignore();
        getline(cin, fname);
        ifstream in(fname);
        if (in.fail())
        {
            cout << "\nSorry, please try again. Entered map couldn't be found\n";
            return false;
        }
        else
        {
            for (int i = 0; i < M.getrow(); i++)
            {
                for (int j = 0; j < M.getcol(); j++)
                {
                    delete M.getmap()[i][j];
                }
            }
        }
    vector<Location*> lines;
    char str1[100], str2[100], str3[100];
    in.getline(str1, 100);
    in.getline(str2, 100);
    in.getline(str3, 100);
    int line = 1, cell = 1;

    while (!in.eof())
    {
        int i = 0, j = 0, k = 1, cost = -1, cell = 0, row = 0, col = 0;
        char name = ' ';
        bool up, down, right, left;
        if (line != 1)
        {
            strcpy(str1, str3);
            in.getline(str2, 100);
            in.getline(str3, 100);
        }
        while (i < strlen(str1) - 1)
        {
            up = down = right = left = true;
            name = ' ';
            if (str1[i] == '+') i++;
            if (str1[i] == '-') up = false;
            else if (str1[i] == ' ') up = true;
            i = i + 3;


            if (str2[j] == '|') left = false;
            else if (str2[j] == ' ') left = true;

            j = j + 2;
            if (str2[j] != ' ')
                if (isdigit(str2[j]))
                    cost = (str2[j] - '0');
                else
                {
                    cost = 0;
                    name = str2[j];
                }
            else
            {
                cost = 0;
            }

            j = j + 2;
            if (str2[j] == '|')
                right = false;
            else if (str2[j] == ' ')
                right = true;


            if (str3[k] == ' ') down = true;
            else if (str3[k] == '-') down = false;
            k = k + 4;

            Location *temp = new Location(left, right, up, down, name, cost);
            lines.push_back(temp);
        }
        M.line(lines);
        lines.clear();
        line++;
    }
    cout << "\nMap has been successfully loaded. Please set start point next.\n";
    return true;
}

bool Setstart(Map& M)
{
    char ch;
    cout << "Where do you want to start from? ";
    cin >> ch;
    for (int i = 0; i < M.getrow(); i++)
    {
        for (int j = 0; j < M.getcol(); j++)
        {
            if (M.getmap()[i][j]->getstart())
            {
                M.getmap()[i][j]->Setstart(false);
            }
            if (M.getmap()[i][j]->getname() == ch)
            {
                M.getmap()[i][j]->Setstart(true);
                return true;
            }
        }
    }
    return false;
}

bool Setfinal(Map& M)
{
    char ch;
    cout << "\nWhere do you want to reach? ";
    cin >> ch;
    for (int i = 0; i < M.getrow(); i++)
    {
        for (int j = 0; j < M.getcol(); j++)
        {
            if (M.getmap()[i][j]->getfinal())
            {
                M.getmap()[i][j]->Setfinal(false);
            }
            if (M.getmap()[i][j]->getname() == ch)
            {
                M.getmap()[i][j]->Setfinal(true);
                return true;
            }
        }
    }
    return false;
}

int main()
{
    int c;
    Map M;
    bool start = false, final = false, path = false, file = false;
    while(1)
    {
        cout<<"Enter your choice from the options\n";
        cout<<"1. Load Map\n";
        cout<<"2. Set Start Point\n";
        cout<<"3. Set End Point\n";
        cout<<"4. Find path using DFS\n";
        cout<<"5. Find path using BFS\n";
        cout<<"6. Quit\n";
        cin>>c;
        switch(c) {
            case 1:
                {
                    file = LoadMap(M);
                    M.setCoordinates();
                }
                break;
            case 2:
                {
                    if(file){
                        start = true;
                        Setstart(M);
                        M.setStart();
                        cout<<"Start point has been set, please choose end point next.\n";
                    }
                    else
                        cout<<"Please Load Map first \n";
                }
                break;
            case 3:
                {
                    if(file){
                        final = true;
                        Setfinal(M);
                        M.setFinal();
                        cout<<"End point has been set, please choose algorithm next.\n";
                    }
                    else
                        cout<<"Please Load Map first \n";
                }
                break;
            case 4:
                {
                    if (start && final){
                        cout << endl;
                        M.DFS();
                        path = true;
                    }
                    else
                        cout << "\nPlease Load Map first\n";
                }
                break;
            case 5:
                {
                    if (start && final){
                        cout << endl;
                        M.BFS();
                        path = true;
                    }
                    else
                        cout << "\nPlease Load Map first\n";
                }
                break;
            case 6:
                    exit(0);
                break;
            default:
                cout<<"Please enter the options from the list\n";
        }
    }
}
