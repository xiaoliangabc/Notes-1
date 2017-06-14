## [参考链接](http://blog.csdn.net/poem_qianmo/article/details/20911629)

### 设定感兴趣区域——ROI（region of interest）
定义ROI区域有两种方法:
- 第一种是使用cv:Rect.顾名思义，cv::Rect表示一个矩形区域。指定矩形的左上角坐标（构造函数的前两个参数）和矩形的长宽（构造函数的后两个参数）就可以定义一个矩形区域。
- 另一种定义ROI的方式是指定感兴趣行或列的范围（Range）。Range是指从起始索引到终止索引（不包括终止索引）的一连段连续序列。cv::Range可以用来定义Range。

### 图像混合——初级线性混合
void addWeighted(InputArray src1, double alpha, InputArray src2, double beta, double gamma, OutputArray dst, int dtype=-1);

 dst = src1[I]×alpha+ src2[I]×beta + gamma;
