#ifndef PLAYER_HPP
#define PLAYER_HPP
#endif
#include<iostream>
#include<set>
#include<algorithm>
#include<list>
#include<iomanip>
using namespace std;
class Player
{
protected:
    /* data */
    int river_array[30];
    int river_array_index;
    int card[20];
    int now_cards;
    int pon[4];
    int gon[4];
    int eat[4][3];
    int pon_index;
    int gon_index;
    int eat_index;
    int reach;
    int double_reach;
    int do_op;

    int check_linshan;
    int check_chankan;
    //東南西北
    int guest_winds;
    int field_winds;

    //和他人
    int long_other;
    set<int> card_river;
    set<int> use_card;
    set<int> yee;//疫牌
    set<int> dolla_arr;//寶牌
    set<int> dolla_arr_li;//寶牌
    set<int> cannot_long;//振聽
public:
    int one_fa;
    int last_card;
    int last_card_other;
    int first_card_start;//天和
    int first_card_after;//地和
    Player();
    ~Player();
    void Add_dolla(int dora);
    void Add_dolla_li(int dora);
    void Add(int card_name);
    bool Remove(int card_name);
    int Count(int card_name);
    bool Check_long();
    void List_card();
    void List_card_long();
    void List_card_river();
    bool Check_gon(int card_name,int state);
    int Check_gon_myself(int get_card);
    bool Check_pon(int card_name);
    bool Check_eat(int card_name);
    void Set_linshan();
    void Reset_linshan();
    void Set_chankan();
    void Reset_chankan();
    void Eat(int card_name_1,int card_name_2,int card_name_3,int now_card);
    void Pon(int card_name);
    void Gon(int card_name);
    void Set_reach();
    void Set_last_card();
    void Set_last_card_other();
    void Set_double_reach();
    void Set_op();
    void Reset_op();
    void Set_long();
    void Reset_long();
    int Retrun_reach();
    int Retrun_no_op();
    void set_winds(int field,int guest);
    void Add_river(int get_card);
    void Reset();
};

Player::Player()
{
    for(int i=0;i<20;i++)card[i] = 1000;
    long_other = 0;
    now_cards = 0;
    pon_index = 0;
    gon_index = 0;
    eat_index = 0;
    reach = 0;
    double_reach = 0;
    do_op = 0;
    one_fa = 0;
    last_card = 0;
    last_card_other = 0;
    check_chankan = 0;
    check_linshan = 0;
    first_card_after = 0;
    first_card_start = 0;
    yee.insert(80);
    yee.insert(88);
    yee.insert(96);
    river_array_index = 0;
    
}


Player::~Player()
{
}
void Player::Reset()
{
    for(int i=0;i<20;i++)card[i] = 1000;
    long_other = 0;
    now_cards = 0;
    pon_index = 0;
    gon_index = 0;
    eat_index = 0;
    reach = 0;
    double_reach = 0;
    do_op = 0;
    one_fa = 0;
    last_card = 0;
    last_card_other = 0;
    check_chankan = 0;
    check_linshan = 0;
    first_card_after = 0;
    first_card_start = 0;
    yee.clear();
    use_card.clear();
    yee.insert(80);
    yee.insert(88);
    yee.insert(96);
    river_array_index = 0;
    dolla_arr.clear();
    dolla_arr_li.clear();
    cannot_long.clear();
    card_river.clear();
}
void Player::Set_op()
{
    do_op = 1;
}
void Player::Reset_op()
{
    do_op = 0;
}
void Player::Set_reach()
{
    reach = 1;
}
void Player::Set_last_card()
{
    last_card = 1;
}
void Player::Set_last_card_other()
{
    last_card_other = 1;
}
void Player::Set_double_reach()
{
    double_reach = 1;
}
int Player::Retrun_reach()
{
    return reach;
}
int Player::Retrun_no_op()
{
    return do_op;
}
void Player::Add(int card_name)
{
    card[now_cards] = card_name;
    now_cards++;

    sort(card,card+20);
}
bool Player::Remove(int card_name)
{
    int now = -1;
    for(int i=0;i<now_cards;i++)
    {
        if(card[i]==card_name)
        {
            now = i;
            card[i] = 1000;
            break;
        }
    }
    if(now==-1)
    {
        //cout<<"error happen in remove "<<card_name<<endl;
        return false;
    }
    now_cards--;
    sort(card,card+20);
    return true;
}
int Player::Count(int card_name)
{
    int ans = 0;
    for(int i=0;i<now_cards;i++)
    {
        if(card[i]==card_name)ans++;
    }
    return ans;
}
bool Player::Check_long()
{
    set<int> more_than_two;
    int tmp[20];
    int tmp_cards = now_cards;
    for(int i=0;i<now_cards;i++)
    {
        if(this->Count(card[i]) >= 2)more_than_two.insert(card[i]);
        tmp[i] = card[i];
    }
    while(more_than_two.size())
    {
        int top = *(more_than_two.begin());
        more_than_two.erase(top);
        //cout<<"now check "<<top<<endl;
        this->Remove(top);
        this->Remove(top);
       
        for(int i=0;i<now_cards;i++)
        {
            if(this->Count(card[i])>=3)
            {
                //cout<<"i find three "<<card[i]<<endl;
                this->Remove(card[i]);
                this->Remove(card[i]);
                this->Remove(card[i]);
                i = -1;
            }
        }
        bool ok = true;
        while(now_cards)
        {
            //cout<<"now cards "<<now_cards<<endl;
            int now_num = card[0];
            //cout<<"now num "<<now_num<<endl;
            if(this->Count(now_num+1)==0||this->Count(now_num+2)==0)
            {
                //cout<<"no long"<<endl;
                ok = false;
                break;
            }
            else
            {
                this->Remove(now_num);
                this->Remove(now_num+1);
                this->Remove(now_num+2);
            }
            //List_card();
        }
        for(int i=0;i<tmp_cards;i++)card[i] = tmp[i];
        now_cards = tmp_cards;
        if(ok==true)return true;
    }
    return false;
}

void Player::List_card()
{
    cout<<"list\n";
    cout<<"now you have "<<now_cards<<" cards"<<endl;
    for(int i=0;i<now_cards;i++)
    {
        if(card[i]>45)
        {
            switch (card[i])
            {
            case 48:
                cout<<"東 ";
                break;
            case 56:
                cout<<"南 ";
                break;
            case 64:
                cout<<"西 ";
                break;
            case 72:
                cout<<"北 ";
                break;
            case 80:
                cout<<"白 ";
                break;
            case 88:
                cout<<"發 ";
                break;
            case 96:
                cout<<"中 ";
                break;
            default:
                break;
            }
        }
        else
        {
            if(card[i]==0||card[i]==16||card[i]==32)cout<<"一 ";
            if(card[i]==1||card[i]==17||card[i]==33)cout<<"二 ";
            if(card[i]==2||card[i]==18||card[i]==34)cout<<"三 ";
            if(card[i]==3||card[i]==19||card[i]==35)cout<<"四 ";
            if(card[i]==4||card[i]==20||card[i]==36)cout<<"五 ";
            if(card[i]==5||card[i]==21||card[i]==37)cout<<"六 ";
            if(card[i]==6||card[i]==22||card[i]==38)cout<<"七 ";
            if(card[i]==7||card[i]==23||card[i]==39)cout<<"八 ";
            if(card[i]==8||card[i]==24||card[i]==40)cout<<"九 ";
        }
    }
    cout<<"\n";
    for(int i=0;i<now_cards;i++)
    {
        if(card[i]/9==0)cout<<"萬 ";
        else if(card[i]/9<=2)cout<<"筒 ";
        else if(card[i]/9<=4)cout<<"條 ";
        else if(card[i]<=72)cout<<"風 ";
        else cout<<"   ";
    }
    cout<<"\n";
    for(int i=0;i<now_cards;i++)
    {
        cout<<setw(2)<<card[i]<<" ";        
    }
    cout<<"\n";
    cout<<"鳴牌"<<endl;
    int tmp[20];
    int index = 0;
    for(int i=0;i<eat_index;i++)
    {
        for(int j=0;j<3;j++)tmp[index++] = eat[i][j];
    }
    for(int i=0;i<pon_index;i++)
    {
        for(int j=0;j<3;j++)tmp[index++] = pon[i];
    }
    for(int i=0;i<gon_index;i++)
    {
        for(int j=0;j<4;j++)tmp[index++] = gon[i];
    }
    for(int i=0;i<index;i++)
    {
        if(tmp[i]>45)
        {
            switch (tmp[i])
            {
            case 48:
                cout<<"東 ";
                break;
            case 56:
                cout<<"南 ";
                break;
            case 64:
                cout<<"西 ";
                break;
            case 72:
                cout<<"北 ";
                break;
            case 80:
                cout<<"白 ";
                break;
            case 88:
                cout<<"發 ";
                break;
            case 96:
                cout<<"中 ";
                break;
            default:
                break;
            }
        }
        else
        {
            if(tmp[i]==0||tmp[i]==16||tmp[i]==32)cout<<"一 ";
            if(tmp[i]==1||tmp[i]==17||tmp[i]==33)cout<<"二 ";
            if(tmp[i]==2||tmp[i]==18||tmp[i]==34)cout<<"三 ";
            if(tmp[i]==3||tmp[i]==19||tmp[i]==35)cout<<"四 ";
            if(tmp[i]==4||tmp[i]==20||tmp[i]==36)cout<<"五 ";
            if(tmp[i]==5||tmp[i]==21||tmp[i]==37)cout<<"六 ";
            if(tmp[i]==6||tmp[i]==22||tmp[i]==38)cout<<"七 ";
            if(tmp[i]==7||tmp[i]==23||tmp[i]==39)cout<<"八 ";
            if(tmp[i]==8||tmp[i]==24||tmp[i]==40)cout<<"九 ";
        }
    }
    cout<<"\n";
    for(int i=0;i<index;i++)
    {
        if(tmp[i]/9==0)cout<<"萬 ";
        else if(tmp[i]/9<=2)cout<<"筒 ";
        else if(tmp[i]/9<=4)cout<<"條 ";
        else if(tmp[i]<=72)cout<<"風 ";
        else cout<<"   ";
    }
    cout<<"\n";
    for(int i=0;i<index;i++)
    {
        cout<<setw(2)<<tmp[i]<<" ";        
    }
    cout<<"\n";
}
bool Player::Check_eat(int card_name)
{
    int count_array[4];
    count_array[0] = this->Count(card_name-2);
    count_array[1] = this->Count(card_name-1);
    count_array[2] = this->Count(card_name+1);
    count_array[3] = this->Count(card_name+2);
    if(count_array[0]>0&&count_array[1]>0)return true;
    if(count_array[1]>0&&count_array[2]>0)return true;
    if(count_array[2]>0&&count_array[3]>0)return true;
    else return false;
}
//state 0 for myself 1 for other
bool Player::Check_gon(int card_name,int state)
{
    int can_gon = this->Count(card_name);
    if(can_gon==3)return true;

    for(int i=0;i<gon_index;i++)
    {
        if(gon[i]==card_name&&state==0) return true;
    }

    return false;
}
bool Player::Check_pon(int card_name)
{
    int can_pon = this->Count(card_name);
    if(can_pon>=2)return true;
    else return false;
}
void Player::Eat(int card_name_1,int card_name_2,int card_name_3,int now_card)
{
    if(card_name_1!=now_card)
    this->Remove(card_name_1);
    if(card_name_2!=now_card)
    this->Remove(card_name_2);
    if(card_name_3!=now_card)
    this->Remove(card_name_3);
    eat[eat_index][0] = card_name_1;
    eat[eat_index][1] = card_name_2;
    eat[eat_index++][2] = card_name_3;
    use_card.insert(card_name_1);
    use_card.insert(card_name_2);
    use_card.insert(card_name_3);
    do_op = 1;
}
void Player::Pon(int card_name)
{
    this->Remove(card_name);
    this->Remove(card_name);
    use_card.insert(card_name);
    do_op = 1;
    pon[pon_index++] = card_name;

}
void Player::Gon(int card_name)
{
    if(this->Count(card_name)==3)
    {
        this->Remove(card_name);
        this->Remove(card_name);
        this->Remove(card_name);
        do_op = 1;
        gon[gon_index++] = card_name;
    }
    else if(this->Count(card_name)==4)
    {
        for(int i=0;i<4;i++)this->Remove(card_name);
        gon[gon_index++] = card_name;
    }
    else if(this->Count(card_name)==1)
    {
        for(int i=0;i<gon_index;i++)
        {
            if(gon[i]==card_name)
            {
                this->Remove(card_name);
                return ;
            }
        }
        cout<<"error happen "<<endl;
    }
    return ;    
}
void Player::List_card_long()
{
    cout<<"you're cards\n"<<endl;
    for(int i=0;i<eat_index;i++)
    {
        card[now_cards++] = eat[i][0];
        card[now_cards++] = eat[i][1];
        card[now_cards++] = eat[i][2];
    }
    for(int i=0;i<pon_index;i++)
    {
        card[now_cards++] = pon[i];
        card[now_cards++] = pon[i];
        card[now_cards++] = pon[i];
    }
    for(int i=0;i<gon_index;i++)
    {
        card[now_cards++] = gon[i];
        card[now_cards++] = gon[i];
        card[now_cards++] = gon[i];
        card[now_cards++] = gon[i];
    }
    for(int i=0;i<now_cards;i++)
    {
        if(card[i]>45)
        {
            switch (card[i])
            {
            case 48:
                cout<<"東 ";
                break;
            case 56:
                cout<<"南 ";
                break;
            case 64:
                cout<<"西 ";
                break;
            case 72:
                cout<<"北 ";
                break;
            case 80:
                cout<<"白 ";
                break;
            case 88:
                cout<<"發 ";
                break;
            case 96:
                cout<<"中 ";
                break;
            default:
                break;
            }
        }
        else
        {
            if(card[i]==0||card[i]==16||card[i]==32)cout<<"一 ";
            if(card[i]==1||card[i]==17||card[i]==33)cout<<"二 ";
            if(card[i]==2||card[i]==18||card[i]==34)cout<<"三 ";
            if(card[i]==3||card[i]==19||card[i]==35)cout<<"四 ";
            if(card[i]==4||card[i]==20||card[i]==36)cout<<"五 ";
            if(card[i]==5||card[i]==21||card[i]==37)cout<<"六 ";
            if(card[i]==6||card[i]==22||card[i]==38)cout<<"七 ";
            if(card[i]==7||card[i]==23||card[i]==39)cout<<"八 ";
            if(card[i]==8||card[i]==24||card[i]==40)cout<<"九 ";
        }
    }
    cout<<"\n";
    for(int i=0;i<now_cards;i++)
    {
        if(card[i]/9==0)cout<<"萬 ";
        else if(card[i]/9<=2)cout<<"筒 ";
        else if(card[i]/9<=4)cout<<"條 ";
        else if(card[i]<=72)cout<<"風 ";
        else cout<<"   ";
    }
    cout<<"\n";
    for(int i=0;i<now_cards;i++)
    {
        cout<<setw(2)<<card[i]<<" ";        
    }
    cout<<"\n";

    cout<<"寶牌"<<endl;
    for(auto i = dolla_arr.begin();i!=dolla_arr.end();i++)
    {
        int x = (*i);
        if(x>45)
        {
            switch (x)
            {
            case 48:
                cout<<"東 ";
                break;
            case 56:
                cout<<"南 ";
                break;
            case 64:
                cout<<"西 ";
                break;
            case 72:
                cout<<"北 ";
                break;
            case 80:
                cout<<"白 ";
                break;
            case 88:
                cout<<"發 ";
                break;
            case 96:
                cout<<"中 ";
                break;
            default:
                break;
            }
        }
        else
        {
            if(x==0||x==16||x==32)cout<<"一 ";
            if(x==1||x==17||x==33)cout<<"二 ";
            if(x==2||x==18||x==34)cout<<"三 ";
            if(x==3||x==19||x==35)cout<<"四 ";
            if(x==4||x==20||x==36)cout<<"五 ";
            if(x==5||x==21||x==37)cout<<"六 ";
            if(x==6||x==22||x==38)cout<<"七 ";
            if(x==7||x==23||x==39)cout<<"八 ";
            if(x==8||x==24||x==40)cout<<"九 ";
        }
    }
    cout<<"\n";
    for(auto i = dolla_arr.begin();i!=dolla_arr.end();i++)
    {
        int x = (*i);
        if(x/9==0)cout<<"萬 ";
        else if(x/9<=2)cout<<"筒 ";
        else if(x/9<=4)cout<<"條 ";
        else if(x<=72)cout<<"風 ";
        else cout<<"  ";
    }
    cout<<"\n";
    for(auto i = dolla_arr.begin();i!=dolla_arr.end();i++)
    {
        int x = (*i);
        cout<<setw(2)<<x<<" ";        
    }
    cout<<"\n";
    if(this->Retrun_reach()==0)return;
    cout<<"裏寶牌"<<endl;
    for(auto i = dolla_arr_li.begin();i!=dolla_arr_li.end();i++)
    {
        int x = (*i);
        if(x>45)
        {
            switch (x)
            {
            case 48:
                cout<<"東 ";
                break;
            case 56:
                cout<<"南 ";
                break;
            case 64:
                cout<<"西 ";
                break;
            case 72:
                cout<<"北 ";
                break;
            case 80:
                cout<<"白 ";
                break;
            case 88:
                cout<<"發 ";
                break;
            case 96:
                cout<<"中 ";
                break;
            default:
                break;
            }
        }
        else
        {
            if(x==0||x==16||x==32)cout<<"一 ";
            if(x==1||x==17||x==33)cout<<"二 ";
            if(x==2||x==18||x==34)cout<<"三 ";
            if(x==3||x==19||x==35)cout<<"四 ";
            if(x==4||x==20||x==36)cout<<"五 ";
            if(x==5||x==21||x==37)cout<<"六 ";
            if(x==6||x==22||x==38)cout<<"七 ";
            if(x==7||x==23||x==39)cout<<"八 ";
            if(x==8||x==24||x==40)cout<<"九 ";
        }
    }
    cout<<"\n";
    for(auto i = dolla_arr_li.begin();i!=dolla_arr_li.end();i++)
    {
        int x = (*i);
        if(x/9==0)cout<<"萬 ";
        else if(x/9<=2)cout<<"筒 ";
        else if(x/9<=4)cout<<"條 ";
        else if(x<=72)cout<<"風 ";
        else cout<<"  ";
    }
    cout<<"\n";
    for(auto i = dolla_arr_li.begin();i!=dolla_arr_li.end();i++)
    {
        int x = (*i);
        cout<<setw(2)<<x<<" ";        
    }
    cout<<"\n";
}
void Player::set_winds(int field,int guest)
{
    field_winds = field;
    guest_winds = guest;
}
void Player::Set_long()
{
    long_other = 1;
    return;
}
void Player::Reset_long()
{
    long_other = 0;
    return;
}
void Player::Add_dolla(int dora)
{
    dolla_arr.insert(dora);
    return;
}
void Player::Add_dolla_li(int dora)
{
    dolla_arr_li.insert(dora);
    return;
}
void Player::Add_river(int get_card)
{
    card_river.insert(get_card);
    river_array[river_array_index++] = get_card;
    return;
}
void Player::List_card_river()
{
    cout<<"river"<<"\n";
    for(int i=0;i<river_array_index;i++)
    {
        if(river_array[i]>45)
        {
            switch (river_array[i])
            {
            case 48:
                cout<<"東 ";
                break;
            case 56:
                cout<<"南 ";
                break;
            case 64:
                cout<<"西 ";
                break;
            case 72:
                cout<<"北 ";
                break;
            case 80:
                cout<<"白 ";
                break;
            case 88:
                cout<<"發 ";
                break;
            case 96:
                cout<<"中 ";
                break;
            default:
                break;
            }
        }
        else
        {
            if(river_array[i]==0||river_array[i]==16||river_array[i]==32)cout<<"一 ";
            if(river_array[i]==1||river_array[i]==17||river_array[i]==33)cout<<"二 ";
            if(river_array[i]==2||river_array[i]==18||river_array[i]==34)cout<<"三 ";
            if(river_array[i]==3||river_array[i]==19||river_array[i]==35)cout<<"四 ";
            if(river_array[i]==4||river_array[i]==20||river_array[i]==36)cout<<"五 ";
            if(river_array[i]==5||river_array[i]==21||river_array[i]==37)cout<<"六 ";
            if(river_array[i]==6||river_array[i]==22||river_array[i]==38)cout<<"七 ";
            if(river_array[i]==7||river_array[i]==23||river_array[i]==39)cout<<"八 ";
            if(river_array[i]==8||river_array[i]==24||river_array[i]==40)cout<<"九 ";
        }
    }
    cout<<"\n";
    for(int i=0;i<river_array_index;i++)
    {
        if(river_array[i]/9==0)cout<<"萬 ";
        else if(river_array[i]/9<=2)cout<<"筒 ";
        else if(river_array[i]/9<=4)cout<<"條 ";
        else if(river_array[i]<=72)cout<<"風 ";
        else cout<<"   ";
    }
    cout<<"\n";
    for(int i=0;i<river_array_index;i++)
    {
        cout<<setw(2)<<river_array[i]<<" ";        
    }
    cout<<"\n";
}
int Player::Check_gon_myself(int get_card)
{
    for(int i=0;i<now_cards;i++)
    {
        if(this->Count(card[i])==4)return card[i];
    }
    for(int i=0;i<gon_index;i++)
    {
        if(gon[i]==get_card)return get_card;
    }
    return -1;
}
void Player::Set_linshan()
{
    check_linshan = 1;
}
void Player::Reset_linshan()
{
    check_linshan = 0;
}
void Player::Set_chankan()
{
    check_chankan = 1;
}
void Player::Reset_chankan()
{
    check_chankan = 0;
}