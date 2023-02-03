#ifndef FANG_CAL_HPP
#define FANG_CAL_HPP
#endif
#include<iostream>
#include"player.hpp"
using namespace std;
class Fang_cal:public Player
{
private:
    /* data */
    int anko;
    int eye;
    int is_seven;
    int final_fang[42];
public:
    Fang_cal();
    ~Fang_cal();
    int Howmany_fang(int get_card);
    int reach(int get_card);//立直 0
    int tsumo();//門前清自摸 1
    int ippatsu();//一發 2
    int Thanyao(int get_card);//段么 3
    int pinf(int get_card);//平和 4
     int epako();//一盃口 5
    int yakuhai();//役牌 6
    int linshan();//領上 7 
    int chankan();//搶槓 8
    int high_tay();//海底 9
    int houtei();//河底 10
    int dora(int get_card);//寶牌 11
    int sanshoku();//三色同順 12
    int sandoko();//三色同刻 13
    int ikkitsukan();//一氣通貫 14
    int toy_toy();//對對 15
    int san_anko();//三暗刻 16
    int sankanz();//三槓子 17 
    int cheat_toys();//七對子 18
    int chanta();//混全帶么 19
    int honlouto();//混老頭 20
    int shosangen();//小三元 21
    int dubry();//雙立直 22
    int honitsu();//混一色 23
    int jun_chan();//純全帶么 24
    int liang_peko();//二盃口 25
    int chinitsu();//清一色 26
    int kokushi();//國士 27
    int kokushi_13(int get_card);//國士13面 28
    int daisangen();//大三元 29
    int sue_ann(int get_card);//四暗 30
    int two_e_saw();//字一色 31
    int ryu_eso();//綠一色 32
    int show_sucy();//小四 33
    int daisy();//大四 34
    int chin_lo();//清老頭 35
    int tureen();//九連 36
    int real_tureen(int get_card);//純正九連 37
    int sukants();//四槓 38
    int tenhou();//天和 39
    int qihou();//地和 40
    int nagashi();//流局 41
    int tmpcal(int get_card);
    //數支役滿自行計算

    int check_reach();
    int check_special(int get_card);
    void print_fang();
    bool check_cannot_long(int get_card);
};

Fang_cal::Fang_cal()
{
    anko=0;
    eye = 0;
    is_seven = 0;
    for(int i=0;i<42;i++)final_fang[i] = 0;
}

Fang_cal::~Fang_cal()
{
}
int Fang_cal::Howmany_fang(int get_card)
{
    for(int i=0;i<42;i++)final_fang[i] = 0;
    use_card.clear();
    for(int i=0;i<now_cards;i++)use_card.insert(card[i]);
    for(int i=0;i<eat_index;i++)
    {
        for(int j=0;j<3;j++)
        use_card.insert(eat[i][j]);
    }
    for(int i=0;i<pon_index;i++)use_card.insert(pon[i]);
    for(int i=0;i<gon_index;i++)use_card.insert(gon[i]);
    int ans = 0;
    //判國士 or 13聽
    ans = kokushi_13(get_card);
    if(ans>0)
    {
        if(ans==13)final_fang[27] = 13;
        if(ans==26)final_fang[28] = 26;
        return ans;
    }
    //判純九連
    ans = real_tureen(get_card);
    if(ans==26)
    {
        final_fang[37] = 26;
        return ans;
    }
    //判九連
    
    ans = tureen();
    if(ans==13)
    {
        final_fang[36] = 13;
        return ans;
    }
    ans = tenhou();
    //cout<<"天和 "<<ans<<endl;
    if(ans>0)
    {
        final_fang[39] = 13;
        return ans;
    }
    ans = qihou();
    //cout<<"地和 "<<ans<<endl;
    if(ans>0)
    {
        final_fang[40] = 13;
        return ans;
    }
    ans = 0;

    ans += daisangen();

    final_fang[29] = ans;
    //cout<<"大三 "<<ans<<endl;
    
    ans += sue_ann(get_card);
    //cout<<"四暗 "<<sue_ann(get_card)<<endl;
    final_fang[30] = sue_ann(get_card);
    

    ans += two_e_saw();
    final_fang[31] = two_e_saw();
    //cout<<"字一色 "<<two_e_saw()<<endl;

    ans += ryu_eso();
    final_fang[32] = ryu_eso();
    //cout<<"綠一色 "<<ryu_eso()<<endl;

    ans += show_sucy();
    final_fang[33] = show_sucy();
    //cout<<"小四 "<<show_sucy()<<endl;

    ans += daisy();
    final_fang[34] = daisy();
    //cout<<"大四 "<<daisy()<<endl;

    ans += chin_lo();
    final_fang[35] = chin_lo();
    //cout<<"清老頭 "<<chin_lo()<<endl;

    ans += sukants();
    final_fang[38] = sukants();
    //cout<<"四槓 "<<sukants()<<endl;
    if(ans>0)return ans;

    ans = 0;
    //判七對子
    ans += cheat_toys();
    final_fang[18] = cheat_toys();
    //cout<<"七對 "<<ans<<endl;
    if(ans>0)is_seven = 1;
    //判斷么
    //cout<<"size"<<use_card.size()<<endl;
    ans += Thanyao(get_card);
    final_fang[3] = Thanyao(get_card);
    
    
    //判立直，門清自摸，一發
    ans += reach(get_card);
    final_fang[0] = reach(get_card);
    //cout<<"立直 "<<reach(get_card);
    
    
    

    //判三槓子
    
    //cout<<"三槓子 "<<sankanz();
    //cout<<ans<<endl;
    set<int> two;
    int tmp[20];
    int tmp_cards = now_cards;
    
    for(int i=0;i<now_cards;i++)
    {
        if(this->Count(card[i])>=2)two.insert(card[i]);
        tmp[i] = card[i];
    }
    int big_ans = 0;
    int tmpp[42];
    for(int j=0;j<42;j++)tmpp[j] = final_fang[j];
    bool is_biger = false;
    for(auto i = two.begin();i!=two.end();i++)
    {
        //cout<<now_cards<<endl;
        int tmp_ans = 0;
        int e = (*i);
        this->Remove(e);
        this->Remove(e);
        eye = e;
        int tmp_eat_index = eat_index;
        int tmp_pon_index = pon_index;
        bool is_ok = true;
        
        
        while(now_cards)
        {
            
            int x = card[0];
            if(this->Count(x)>2)
            {
                this->Remove(x);
                this->Remove(x);
                this->Remove(x);
                pon[pon_index++] = x;
            }
            else 
            {
                bool ok[3];
                for(int j=0;j<3;j++)ok[j] = this->Remove(x+j);
                if(ok[0]==false||ok[1]==false||ok[2]==false)
                {
                    is_ok=false;
                    break;
                }
                for(int j=0;j<3;j++)eat[eat_index][j] = x+j;
                eat_index++;
            }
        }
        anko = pon_index - tmp_pon_index ;
        if(is_ok==true)
        tmp_ans = tmpcal(get_card);
        if(big_ans<tmp_ans)
        {
            is_biger = true;
            for(int j=0;j<42;j++)tmpp[j] = final_fang[j] ;
            big_ans = tmp_ans;
        }
        this->Add(*i);
        this->Add(*i);
        for(int j=0;j<tmp_cards;j++)
        {
            card[j] = tmp[j];
        }
        now_cards = tmp_cards;
        pon_index = tmp_pon_index;
        eat_index = tmp_eat_index;
    }
    ans+=big_ans;
    if(is_biger==true)
    for(int i=0;i<42;i++)final_fang[i]=tmpp[i] ;
    if(ans>0||this->Check_long()==true)//判門清 一發
    {
        //cout<<"門清 "<<tsumo()<<endl;
        ans += ippatsu();
        final_fang[2] = ippatsu();

        final_fang[1] = tsumo();
        ans += tsumo();
    }
    return ans;
}
int Fang_cal::tmpcal(int get_card)
{
    
    int ans = 0;
    
    //盼海底，河底
    ans += high_tay();
    final_fang[9] = high_tay();
    //cout<<"海底 "<<high_tay();

    ans += houtei();
    final_fang[10] = houtei();
    //cout<<"河底 "<<houtei();

    //三槓
    ans += sankanz();
    final_fang[17] = sankanz();

    //判平和
    ans += pinf(get_card);
    final_fang[4] = pinf(get_card);
    //cout<<"平和 "<<pinf(get_card)<<endl;
    //判一盃口
    ans += epako();
    final_fang[5] = epako();
    //cout<<"一盃口 "<<epako()<<endl;

    ans += yakuhai();
    final_fang[6] = yakuhai();
   // cout<<"役牌 "<<yakuhai()<<endl;

    ans += linshan();
    final_fang[7] = linshan();
    //cout<<"領上 "<<linshan()<<endl;

    ans += chankan();
    final_fang[8] = chankan();
    //cout<<"搶槓 "<<chankan()<<endl;

    ans += dora(get_card);
    final_fang[11] = dora(get_card);
    //cout<<"寶牌 "<<dora()<<endl;

    ans += sanshoku();
    final_fang[12] = sanshoku();
    //cout<<"三色同順 "<<sanshoku()<<endl;

    ans += sandoko();
    final_fang[13] = sandoko();
    //cout<<"三色同刻 "<<sandoko()<<endl;

    ans += ikkitsukan();
    final_fang[14] = ikkitsukan();
    //cout<<"一氣 "<<ikkitsukan()<<endl;

    ans += toy_toy();
    final_fang[15] = toy_toy();
    //cout<<"對對 "<<toy_toy()<<endl;

    ans += san_anko();
    final_fang[16] = san_anko();
    //cout<<"三暗刻 "<<san_anko()<<endl;

    ans += chanta();
    final_fang[19] = chanta();
    //cout<<"混全帶么 "<<chanta()<<endl;

    ans += honlouto();
    final_fang[20] = honlouto();
    //cout<<"混老頭 "<<honlouto()<<endl;

    ans += shosangen();
    final_fang[21] = shosangen();
    //cout<<"小三元 "<<shosangen()<<endl;

    ans += dubry();
    final_fang[22] = dubry();
    //cout<<"雙立直 "<<dubry()<<endl;
    
    ans += honitsu();
    final_fang[23] = honitsu();
    //cout<<"混一色 "<<honitsu()<<endl;

    ans += jun_chan();
    final_fang[24] = jun_chan();
    //cout<<"純全帶么 "<<jun_chan()<<endl;

    ans += liang_peko();
    final_fang[25] = liang_peko();
    //cout<<"二盃口 "<<liang_peko()<<endl;

    ans += chinitsu();
    final_fang[26] = chinitsu();
    //cout<<"清一色 "<<chinitsu()<<endl;

    //cout<<"total ans "<<ans<<endl<<endl;
    return ans;
}
int Fang_cal::reach(int get_card)//立直ok
{
    int rea = this->Retrun_reach();
    if(rea==0)return 0;
    int ans = check_special(get_card);
    if(ans>0)return 1;
    bool anss = Check_long();
    if(anss==true)return 1;
    return 0;
}
int Fang_cal::tsumo()//門前清自摸ok
{
    if(this->do_op==1)return 0;
    else if(this->long_other==1)return 0;
    else return 1;
}
int Fang_cal::ippatsu()//一發ok
{
    return this->one_fa;
}
int Fang_cal::Thanyao(int get_card)//段么ok
{
   // cout<<use_card.size()<<endl;
    if(Check_long()==false&&check_special(get_card)==0)return 0;
   // cout<<use_card.size()<<endl;
    set<int>::iterator iter;
    for(iter = use_card.begin();iter!=use_card.end();iter++)
    {
        int num = *iter;
        //cout<<"num"<<num<<endl;
        if(num%8==0)return 0;
    }
    return 1;
    
}
int Fang_cal::pinf(int get_card)//平和ok
{
    if(this->do_op==1)
    return 0;
    for(auto i = yee.begin();i!=yee.end();i++)
    {
        int x = (*i);
        if(x==eye)return 0;
    }
    for(int i=10;i<=12;i++)
    {
        if(eye==i*8)return 0;
    }
    if(pon_index!=0||gon_index!=0||eat_index!=4)return 0;
    for(int i=0;i<4;i++)
    {
        if(eat[i][0]==get_card||eat[i][2]==get_card)return 1;
    }
    return 0;
}
int Fang_cal::epako()//一盃口ok
{
    if(liang_peko()>0)return 0;
    if(this->do_op==1)
    return 0;
    int check_cheat_toys =  cheat_toys();
    if(check_cheat_toys>0)return 0;
    set<pair<int,pair<int,int>>> eat_pair;
    for(int i=0;i<eat_index;i++)
    {
        pair<int,pair<int,int>> tmp_pair = make_pair(eat[i][0],make_pair(eat[i][1],eat[i][2]));
        auto find_pair = eat_pair.find(tmp_pair);
        if(find_pair!=eat_pair.end())return 1;
        eat_pair.insert(tmp_pair);
    }
    return 0;
}
int Fang_cal::yakuhai()//役牌ok
{
    int ans = 0;
    for(auto i = use_card.begin();i!=use_card.end();i++)
    {
        int x = (*i);
        bool find = false;
        for(int j=0;j<pon_index;j++)
        {
            if(pon[j]==x)
            {
                find = true;
                break;
            }
        }
        for(int j=0;j<gon_index;j++)
        {
            if(gon[j]==x)
            {
                find = true;
                break;
            }
        }
        if(find==false)continue;
        if(yee.find(x)!=yee.end())ans+=1;
        if(x==guest_winds)ans+=1;
        if(x==field_winds)ans+=1;
    }
    return ans;
    
}
int Fang_cal::linshan()//領上ok
{

    return check_linshan;
    
}
int Fang_cal::chankan()//搶槓ok
{
    return check_chankan;
    
}
int Fang_cal::high_tay()//海底ok
{
    if(last_card==1)return 1;
    else 
    return 0;
    
}
int Fang_cal::houtei()//河底ok
{
    if(last_card_other == 1)return 1;
    else 
    return 0;
    
}
int Fang_cal::dora(int get_card)//寶牌ok
{    
    int ans = 0;
    for(int i=0;i<now_cards;i++)
    {
        int x = card[i];
        if(dolla_arr.find(x)!=dolla_arr.end())ans+=1;
        if(this->Retrun_reach()!=1)continue;
        if(dolla_arr_li.find(x)!=dolla_arr_li.end())ans+=1;
    }
    for(int i=0;i<eat_index;i++)
    {
        for(int j=0;j<3;j++)
        {
            int x = eat[i][j];
            if(dolla_arr.find(x)!=dolla_arr.end())ans+=1;
            if(this->Retrun_reach()!=1)continue;

            if(dolla_arr_li.find(x)!=dolla_arr_li.end())ans+=1;
        }
    }
    for(int i=0;i<pon_index;i++)
    {
        int x = pon[i];
        if(dolla_arr.find(x)!=dolla_arr.end())ans+=3;
        if(this->Retrun_reach()!=1)continue;
        if(dolla_arr_li.find(x)!=dolla_arr_li.end())ans+=3;
    }
    for(int i=0;i<gon_index;i++)
    {
        int x = gon[i];
        if(dolla_arr.find(x)!=dolla_arr.end())ans+=4;
        if(this->Retrun_reach()!=1)continue;
        if(dolla_arr_li.find(x)!=dolla_arr_li.end())ans+=4;
    }
    if(dolla_arr.find(eye)!=dolla_arr.end())ans+=2;
    if(this->Retrun_reach()!=1)return ans;
    if(dolla_arr_li.find(eye)!=dolla_arr_li.end())ans+=2;
    return ans;
    
}
int Fang_cal::sanshoku()//三色同順ok
{
    if(eat_index<3)return 0;
    set<pair<int,pair<int,int>>> tmp_eat;
    for(int i=0;i<eat_index;i++)
    {
        tmp_eat.insert(make_pair(eat[i][0],make_pair(eat[i][1],eat[i][2])));
    }
    auto first = (*tmp_eat.begin());
    auto first_find = make_pair(first.first+16,make_pair(first.second.first+16,first.second.second+16));
    auto second_find = make_pair(first.first+32,make_pair(first.second.first+32,first.second.second+32));
    auto check_1 = tmp_eat.find(first_find);
    auto check_2 = tmp_eat.find(second_find);
    if(check_1!=tmp_eat.end()&&check_2!=tmp_eat.end())
    {
        if(this->do_op==0)return 2;
        else return 1;
    }
    auto iter = tmp_eat.begin();
    first = (*(++iter));
    first_find = make_pair(first.first+16,make_pair(first.second.first+16,first.second.second+16));
    second_find = make_pair(first.first+32,make_pair(first.second.first+32,first.second.second+32));
    check_1 = tmp_eat.find(first_find);
    check_2 = tmp_eat.find(second_find);
    if(check_1!=tmp_eat.end()&&check_2!=tmp_eat.end())
    {
        if(this->do_op==0)return 2;
        else return 1;
    }
    return 0;
    
}
int Fang_cal::sandoko()//三色同刻ok
{
    set<int> tmp;
    if(pon_index+gon_index<3)return 0;
    
    for(int i=0;i<pon_index;i++)tmp.insert(pon[i]);
    for(int i=0;i<gon_index;i++)tmp.insert(gon[i]);
    auto iter = tmp.begin();
    if(iter==tmp.end())return 0;
    
    int x = (*iter);
    auto check_1 = tmp.find(x+16);
    auto check_2 = tmp.find(x+32);
    if(check_1!=tmp.end()&&check_2!=tmp.end())return 2;
    x = (*(++iter));
    if(iter==tmp.end())return 0;
    check_1 = tmp.find(x+16);
    check_2 = tmp.find(x+32);
    if(check_1!=tmp.end()&&check_2!=tmp.end())return 2;
    return 0;
}
int Fang_cal::ikkitsukan()//一氣通貫ok
{
    if(eat_index<3)return 0;
    set<pair<int,pair<int,int>>> tmp_eat;
    for(int i=0;i<eat_index;i++)
    {
        tmp_eat.insert(make_pair(eat[i][0],make_pair(eat[i][1],eat[i][2])));
    }
    auto first = (*tmp_eat.begin());
    auto first_find = make_pair(first.first+3,make_pair(first.second.first+3,first.second.second+3));
    auto second_find = make_pair(first.first+6,make_pair(first.second.first+6,first.second.second+6));
    auto check_1 = tmp_eat.find(first_find);
    auto check_2 = tmp_eat.find(second_find);
    if(check_1!=tmp_eat.end()&&check_2!=tmp_eat.end())
    {
        if(this->do_op==0)return 2;
        else return 1;
    }
    auto iter = tmp_eat.begin();
    first = (*(++iter));
    first_find = make_pair(first.first+3,make_pair(first.second.first+3,first.second.second+3));
    second_find = make_pair(first.first+6,make_pair(first.second.first+6,first.second.second+6));
    check_1 = tmp_eat.find(first_find);
    check_2 = tmp_eat.find(second_find);
    if(check_1!=tmp_eat.end()&&check_2!=tmp_eat.end())
    {
        if(this->do_op==0)return 2;
        else return 1;
    }
    return 0;

}
int Fang_cal::toy_toy()//對對ok
{
    if(eat_index==0)return 2;
    return 0;
}
int Fang_cal::san_anko()//三暗刻ok
{
    if(anko==3)return 2;
    return 0;
}
int Fang_cal::sankanz()//三槓子ok
{
    if(gon_index==3)return 2;
    else
    return 0;
}
int Fang_cal::cheat_toys()//七對子ok
{

    if(do_op==1)return 0;
    for(auto i = use_card.begin();i!=use_card.end();i++)
    {
        int x = *i;
        if(this->Count(x)!=2)return 0;
    }
    return 2;
}
int Fang_cal::chanta()//混全帶么ok
{
    int check = cheat_toys();
    bool word = false;
    if(check==2)return 0;
    if(eat_index==0)return 0;
    if(eye%8!=0)return 0;

    if(eye>40)word = true;
    for(int i=0;i<eat_index;i++)
    {
        if(eat[i][0]%8==0)continue;
        else if(eat[i][2]%8==0)continue;
        else return 0;
    }
    for(int i=0;i<pon_index;i++)
    {
        if(pon[i]>40)word = true;
        if(pon[i]%8==0)continue;
        else return 0;
    }
    for(int i=0;i<gon_index;i++)
    {
        if(gon[i]>40)word = true;
        if(gon[i]%8==0)continue;
        else return 0;
    }
    if(word==false)return 0;
    if(do_op==1)return 1;
    else return 2;    
}
int Fang_cal::honlouto()//混老頭ok
{
    if(eye%8!=0)return 0;
    if(eat_index>0)return 0;
    for(int i=0;i<pon_index;i++)
    {
        if(pon[i]%8==0)continue;
        else return 0;
    }
    for(int i=0;i<gon_index;i++)
    {
        if(gon[i]%8==0)continue;
        else return 0;
    }
    return 2;
    
}
int Fang_cal::shosangen()//小三元ok
{
    if(eye!=80&&eye!=88&&eye!=96)return 0;
    bool ok[3];
    ok[0] = false;
    ok[1] = false;
    ok[2] = false;
    ok[(eye-80)/8]=true;
    for(int i=0;i<pon_index;i++)
    {
        if(pon[i]<80)continue;
        ok[(pon[i]-80)/8]=true;
    }
    for(int i=0;i<gon_index;i++)
    {
        if(gon[i]<80)continue;
        ok[(gon[i]-80)/8]=true;
    }
    if(ok[0]==true&&ok[1]==true&&ok[2]==true)return 2;
    else return 0;
    
}
int Fang_cal::dubry()//雙立直ok
{
    return double_reach;
    
}
int Fang_cal::honitsu()//混一色ok
{
    auto iter = use_card.begin();
    int number = (*iter);
    if(number>40)return 0;
    int which;
    if(number<9)which = 0;
    else if(number<25)which = 1;
    else if(number<41)which = 2;
    bool word = false;
    for(iter = use_card.begin();iter!=use_card.end();iter++)
    {
        int x = (*iter);
        if(x>40)
        {
            word = true;
            break;
        }
        if(which==0&&x>8)return 0;
        else if(which==1&&(x<16||x>24))return 0;
        else if(which==2&&x<32)return 0;
    }
    if(word==false)return 0;
    if(do_op==1)return 2;
    else return 3;
}
int Fang_cal::jun_chan()//純全帶么ok
{
    int check = cheat_toys();
    if(check==2)return 0;
    if(eat_index==0)return 0;
    if(eye%8!=0)return 0;

    if(eye>40)return 0;
    for(int i=0;i<eat_index;i++)
    {
        if(eat[i][0]%8==0)continue;
        else if(eat[i][2]%8==0)continue;
        else return 0;
    }
    for(int i=0;i<pon_index;i++)
    {
        if(pon[i]>40)return 0;
        if(pon[i]%8==0)continue;
        else return 0;
    }
    for(int i=0;i<gon_index;i++)
    {
        if(gon[i]>40)return 0;
        if(gon[i]%8==0)continue;
        else return 0;
    }

    if(do_op==1)return 2;
    else return 3;    
    
}
int Fang_cal::liang_peko()//二盃口ok
{
    if(do_op==1)return 0;
    if(eat_index!=4)return 0;
    set<pair<int,pair<int,int>>> tmp_eat;
    for(int i=0;i<eat_index;i++)
    {
        tmp_eat.insert(make_pair(eat[i][0],make_pair(eat[i][1],eat[i][2])));
    }
   
    if(tmp_eat.size()!=2)return 0;
    if(is_seven==1)return 1;
    else return 3;
    
}
int Fang_cal::chinitsu()//清一色ok
{
    auto iter = use_card.begin();
    int number = (*iter);
    if(number>40)return 0;
    int which;
    if(number<9)which = 0;
    else if(number<25)which = 1;
    else if(number<41)which = 2;
    bool word = false;
    for(iter = use_card.begin();iter!=use_card.end();iter++)
    {
        int x = (*iter);
        if(x>40)
        {
            return 0;
        }
        if(which==0&&x>8)return 0;
        else if(which==1&&(x<16||x>24))return 0;
        else if(which==2&&x<32)return 0;
    }
    if(do_op==1)return 5;
    else return 6;
    
}
int Fang_cal::kokushi()//國士ok
{
    for(int i=0;i<13;i++)
    {
        bool check = true;
        if(this->Count(i*8)==2)
        {
            for(int j=0;j<13;j++)
            {
                if(j!=i && this->Count(j*8)!=1)
                {
                    check = false;
                    break;
                }
            }
        }
        else continue;
        if(check==true)
        {
            return 13;
        }
    }
    return 0;
}
int Fang_cal::kokushi_13(int get_card)//國士13面ok
{
    int ans = kokushi();
    if(ans==13)
    {
        if(this->Count(get_card)==2)return 26;
        else return 13;
    }
    return 0;
    
}
int Fang_cal::daisangen()//大三元ok
{
    bool ok[3];
    ok[0] = false;
    ok[1] = false;
    ok[2] = false;
    for(int i=0;i<pon_index;i++)
    {

        if(pon[i]<80)continue;
        ok[(pon[i]-80)/8]=true;
    }
    for(int i=0;i<gon_index;i++)
    {
        if(gon[i]<80)continue;
        ok[(gon[i]-80)/8]=true;
    }
    //cout<<"here"<<endl;
    if(ok[0]==true&&ok[1]==true&&ok[2]==true)return 13;
    else return 0;    
}
int Fang_cal::sue_ann(int get_card)//四暗ok
{
    if(get_card==eye)return 0;
    if(anko==4)return 13;
    else return 0;
    
}
int Fang_cal::two_e_saw()//字一色ok
{
    for(auto i = use_card.begin();i!=use_card.end();i++)
    {
        int x = *i;
        if(x<=40)return 0;
    }
    return 13;
    
}
int Fang_cal::ryu_eso()//綠一色ok
{
    for(auto i = use_card.begin();i!=use_card.end();i++)
    {
        int x = *i;
        if(x!=33&&x!=34&&x!=35&&x!=37&&x!=39&&x!=88)return 0;
    }
    return 13;
    
}
int Fang_cal::show_sucy()//小四ok
{
    if(eye!=48&&eye!=56&&eye!=64&&eye!=72)return 0;
    bool ok[4];
    for(int i=0;i<4;i++)ok[i] = false;
    ok[(eye-48)/8] = true;
    for(int i=0;i<pon_index;i++)
    {
        int x = pon[i];
        if(x==48||x==56||x==64||x==72)
        {
            ok[(x-48)/8] = true;
        }
    }
    for(int i=0;i<gon_index;i++)
    {
        int x = gon[i];
        if(x==48||x==56||x==64||x==72)
        {
            ok[(x-48)/8] = true;
        }
    }
    if(ok[0]==false||ok[1]==false||ok[2]==false||ok[3]==false)return 0;
    else return 13;
    
}
int Fang_cal::daisy()//大四Ok
{
    bool ok[4];
    for(int i=0;i<4;i++)ok[i] = false;
    for(int i=0;i<pon_index;i++)
    {
        int x = pon[i];
        if(x==48||x==56||x==64||x==72)
        {
            ok[(x-48)/8] = true;
        }
    }
    for(int i=0;i<gon_index;i++)
    {
        int x = gon[i];
        if(x==48||x==56||x==64||x==72)
        {
            ok[(x-48)/8] = true;
        }
    }
    if(ok[0]==false||ok[1]==false||ok[2]==false||ok[3]==false)return 0;
    else return 26;
}
int Fang_cal::chin_lo()//清老頭ok
{
    for(auto i = use_card.begin();i!=use_card.end();i++)
    {
        int x = *i;
        if(x!=0&&x!=8&&x!=16&&x!=24&&x!=32&&x!=40)return 0;
    }
    return 13;
    
}
int Fang_cal::tureen()//九連ok
{
    bool find = false;
    int tmp_num = 0;
    for(int i=0;i<9;i++)
    {
        if(this->Count(i)==2)
        {
            find = true;
            this->Remove(i);
            tmp_num = i;
            break;
        }
    }
    if(find==false)
    {
        return 0;
    }

    if(this->Count(0)==3&&this->Count(1)==1&&this->Count(2)==1&&
        this->Count(3)==1&&this->Count(4)==1&&this->Count(5)==1&&
        this->Count(6)==1&&this->Count(7)==1&&this->Count(8)==3)
        {
            this->Add(tmp_num);
            return 13;            
        }
        
    this->Add(tmp_num);
    return 0;
}
int Fang_cal::real_tureen(int get_card)//純正九連ok
{
    this->Remove(get_card);
    if(this->Count(0)==3&&this->Count(1)==1&&this->Count(2)==1&&
        this->Count(3)==1&&this->Count(4)==1&&this->Count(5)==1&&
        this->Count(6)==1&&this->Count(7)==1&&this->Count(8)==3)
    {
        this->Add(get_card);
        return 26;
    }
    this->Add(get_card);
    return 0;
    
}
int Fang_cal::sukants()//四槓ok
{
    if(gon_index==4)return 13;
    else
    return 0;
    
}
int Fang_cal::tenhou()//天和
{
    bool is_long = Check_long();
    if(first_card_start==1&&is_long==true)return 13;
    else return 0;
    
}
int Fang_cal::qihou()//地和
{
    bool is_long = Check_long();
    if(first_card_after==1&&is_long==true)return 13;
    else return 0;
    
}
int Fang_cal::nagashi()//流局
{
    set<int>::iterator iter;
    for(iter = card_river.begin();iter!=card_river.end();iter++)
    {
        int num = *iter;
        if(num%8!=0)return 0;
    }
    return 4;
    
}
int Fang_cal::check_reach()
{
    if(do_op==1)return 0;
    for(int j=0;j<now_cards;j++)
    {
        //cout<<use_card.size()<<endl;
        int y = card[j];
        this->Remove(y);
        bool find = false;
        for(int i=0;i<=8;i++)
        {
            this->Add(i);
            find = Check_long();
            int ans = check_special(i);
            if(find==true||ans>0)
            {
                //cout<<ans<<endl;
                this->Remove(i);
                this->Add(y);
                //cout<<"card is "<<i<<endl;
                return 1;
            }
            this->Remove(i);
        }
        for(int i=16;i<=24;i++)
        {
            this->Add(i);
            int ans = check_special(i);
            find = Check_long();
            if(find==true||ans>0)
            {
                //cout<<"card is "<<i<<endl;
                this->Add(y);
                this->Remove(i);
                return 1;
            }
            this->Remove(i);
        }

        for(int i=32;i<=40;i++)
        {
            this->Add(i);
            int ans = check_special(i);
            find = Check_long();
            if(find==true||ans>0)
            {
                //cout<<"card is "<<i<<endl;
                this->Add(y);
                this->Remove(i);
                return 1;
            }
            this->Remove(i);
        }
        for(int i=6;i<=12;i++)
        {
            int x = i*8;
            this->Add(x);
            int ans = check_special(x);
        
            find = Check_long();
            if(find==true||ans>0)
            {
                //cout<<"card is "<<x<<endl;
                this->Add(y);
                this->Remove(x);
                return 1;
            }
            this->Remove(x);
        }
        this->Add(y);
    }    
    return 0;
}
int Fang_cal::check_special(int get_card)
{
    if(do_op==1)return 0;
    set<int> tmp;
    for(auto t = use_card.begin();t!=use_card.end();t++)tmp.insert((*t));
    use_card.clear();
    for(int i=0;i<now_cards;i++)use_card.insert(card[i]);
    int ans = 0;
    ans = cheat_toys();
    if(ans>0)
    {
        use_card.clear();
        for(auto t = tmp.begin();t!=tmp.end();t++)use_card.insert((*t));
        return ans;
    }
    ans = kokushi();
    if(ans>0)
    {
        use_card.clear();
        for(auto t = tmp.begin();t!=tmp.end();t++)use_card.insert((*t));
        return ans;
    }
    ans = kokushi_13(get_card);
    if(ans>0)
    {
        use_card.clear();
        for(auto t = tmp.begin();t!=tmp.end();t++)use_card.insert((*t));
        return ans;
    }
    ans = tureen();
    if(ans>0)
    {
        use_card.clear();
        for(auto t = tmp.begin();t!=tmp.end();t++)use_card.insert((*t));
        return ans;
    }
    ans = real_tureen(get_card);
    if(ans>0)
    {
        use_card.clear();
        for(auto t = tmp.begin();t!=tmp.end();t++)use_card.insert((*t));
        return ans;
    }
    return 0;
}
void Fang_cal::print_fang()
{
    if(final_fang[18]==2&&final_fang[25]==1)
    {
        final_fang[18] = 0;
        final_fang[25] = 3;
    }
    if(final_fang[0]>0)cout<<"立直 "<<final_fang[0]<<endl;
    if(final_fang[1]>0)cout<<"門前清自摸 "<<final_fang[1]<<endl;
    if(final_fang[2]>0)cout<<"一發 "<<final_fang[2]<<endl;
    if(final_fang[3]>0)cout<<"斷么九 "<<final_fang[3]<<endl;
    if(final_fang[4]>0)cout<<"平和 "<<final_fang[4]<<endl;
    if(final_fang[5]>0)cout<<"一盃口 "<<final_fang[5]<<endl;
    if(final_fang[6]>0)cout<<"役牌 "<<final_fang[6]<<endl;
    if(final_fang[7]>0)cout<<"領上開花 "<<final_fang[7]<<endl;
    if(final_fang[8]>0)cout<<"搶槓 "<<final_fang[8]<<endl;
    if(final_fang[9]>0)cout<<"海底撈月 "<<final_fang[9]<<endl;
    if(final_fang[10]>0)cout<<"河底撈魚 "<<final_fang[10]<<endl;
    if(final_fang[11]>0)cout<<"寶牌 "<<final_fang[11]<<endl;
    if(final_fang[12]>0)cout<<"三色同順 "<<final_fang[12]<<endl;
    if(final_fang[13]>0)cout<<"三色同刻 "<<final_fang[13]<<endl;
    if(final_fang[14]>0)cout<<"一氣通貫 "<<final_fang[14]<<endl;
    if(final_fang[15]>0)cout<<"對對和 "<<final_fang[15]<<endl;
    if(final_fang[16]>0)cout<<"三暗刻 "<<final_fang[16]<<endl;
    if(final_fang[17]>0)cout<<"三槓子 "<<final_fang[17]<<endl;
    if(final_fang[18]>0)cout<<"七對子"<<final_fang[18]<<endl;
    if(final_fang[19]>0)cout<<"混全帶么 "<<final_fang[19]<<endl;
    if(final_fang[20]>0)cout<<"混老頭 "<<final_fang[20]<<endl;
    if(final_fang[21]>0)cout<<"小三元 "<<final_fang[21]<<endl;
    if(final_fang[22]>0)cout<<"雙立直 "<<final_fang[22]<<endl;
    if(final_fang[23]>0)cout<<"混一色 "<<final_fang[23]<<endl;
    if(final_fang[24]>0)cout<<"純全帶么 "<<final_fang[24]<<endl;
    if(final_fang[25]>0)cout<<"二盃口 "<<final_fang[25]<<endl;
    if(final_fang[26]>0)cout<<"清一色 "<<final_fang[26]<<endl;
    if(final_fang[27]>0)cout<<"國士無雙 "<<final_fang[27]<<endl;
    if(final_fang[28]>0)cout<<"國士無雙13面待聽 "<<final_fang[28]<<endl;
    if(final_fang[29]>0)cout<<"大三元 "<<final_fang[29]<<endl;
    if(final_fang[30]>0)cout<<"四暗刻 "<<final_fang[30]<<endl;
    if(final_fang[31]>0)cout<<"字一色 "<<final_fang[31]<<endl;
    if(final_fang[32]>0)cout<<"綠一色 "<<final_fang[32]<<endl;
    if(final_fang[33]>0)cout<<"小四喜 "<<final_fang[33]<<endl;
    if(final_fang[34]>0)cout<<"大四喜 "<<final_fang[34]<<endl;
    if(final_fang[35]>0)cout<<"清老頭 "<<final_fang[35]<<endl;
    if(final_fang[36]>0)cout<<"九連寶燈 "<<final_fang[36]<<endl;
    if(final_fang[37]>0)cout<<"純正九連寶燈 "<<final_fang[37]<<endl;
    if(final_fang[38]>0)cout<<"四槓子 "<<final_fang[38]<<endl;
    if(final_fang[39]>0)cout<<"天和 "<<final_fang[39]<<endl;
    if(final_fang[40]>0)cout<<"地和 "<<final_fang[40]<<endl;
    if(final_fang[41]>0)cout<<"流局滿貫 "<<final_fang[41]<<endl;
    return ;
}
bool Fang_cal::check_cannot_long(int get_card)
{
    for(int i=0;i<river_array_index;i++)
    {
        if(get_card==river_array[i])return false;
        this->Add(river_array[i]);
        if(this->Howmany_fang(river_array[i])>0)
        {
            this->Remove(river_array[i]);
            return false;
        }
        this->Remove(river_array[i]);

    }
    

    return true;
}