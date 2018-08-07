## 文件读取
### 例1
    ifstream fin(file_name);
    if(!fin){
        cerr<<"没有找到file_name"<<endl;
    }
    while(getline(fin, temp)){
        Vector2d uv;
        double a,b;
        fin>>a>>b;
        uv(0) = a;
        uv(1) = b;
        p2d.emplace_back(uv);
    }
