## 排序
### sort函数
#### vector排序
    vector<Struct> A
    bool f1 (Struct a,Struct b) { return (a.x>b.x); }
    bool f2 (Struct a,Struct b) { return (a.x<b.x); }
    sort(A.begin(), A.end(), f1);//降序排列
    sort(A.begin(), A.end(), f2);//升序排列
    sort(A.begin(), A.end(), \[\](const struct& A, const struct& B){return A.a < B.b;})
#### list排序
    list<Struct> A
    bool f1 (Struct a,Struct b) { return (a.x>b.x); }
    bool f2 (Struct a,Struct b) { return (a.x<b.x); }
    A.sort(boost::bind(&f1, _1, _2))//降序排列
    A.sort(f1)//和上面有区别吗？
    A.sort(boost::bind(&f2, _1, _2))//升序排列
------
### nth_element函数
    vector<int> pts;
    //只保证pts[6]是排名第6的元素,同时pts[0-5]<pts[6],pts[6-end]>pts[6]
    nth_element(pts.begin(), pts.begin()+6; pts.end())
    
    compare(Ponit2d* a, Ponit2d* b)
    {
        return(a->x < b->x);
    }
    vector<point2d> pts;
    nth_element(pts.begin(), pts.begin()+6; pts.end(), compare);

### map排序
    map<int, pair<int, int> > map_dis_id;
    int distance;
    //对id1和id2的距离进行排序
    map_dis_id[distance] = pair<int, int>(id1, id2)
    for(map<int, pair<int, int> >::iterator it = map_dis_id.begin(); it != map_dis_id.end(); it++){
         cout<<(*it).first<<endl;
         cout<<((*it).second).first<<endl;
         cout<<((*it).second).second<<endl;
    }
    
