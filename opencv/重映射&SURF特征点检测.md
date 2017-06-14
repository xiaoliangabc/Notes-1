## [链接](http://blog.csdn.net/poem_qianmo/article/details/30974513)

### remap( )函数解析

void remap(InputArray src, OutputArraydst, InputArray map1, InputArray map2, int interpolation, intborderMode=BORDER_CONSTANT, const Scalar& borderValue=Scalar())

- 第一个参数，InputArray类型的src，输入图像，即源图像，填Mat类的对象即可，且需为单通道8位或者浮点型图像。
- 第二个参数，OutputArray类型的dst，函数调用后的运算结果存在这里，即这个参数用于存放函数调用后的输出结果，需和源图片有一样的尺寸和类型。
- 第三个参数，InputArray类型的map1，它有两种可能的表示对象。
表示点（x，y）的第一个映射。
表示CV_16SC2 , CV_32FC1 或CV_32FC2类型的X值。
- 第四个参数，InputArray类型的map2，同样，它也有两种可能的表示对象，而且他是根据map1来确定表示那种对象。
若map1表示点（x，y）时。这个参数不代表任何值。
表示CV_16UC1 , CV_32FC1类型的Y值（第二个值）。
- 第五个参数，int类型的interp-olation,插值方式，之前的resize( )函数中有讲到，需要注意，resize( )函数中提到的INTER_AREA插值方式在这里是不支持的，所以可选的插值方式如下：
 - INTER_NEAREST - 最近邻插值
 - INTER_LINEAR – 双线性插值（默认值）
 - INTER_CUBIC – 双三次样条插值（逾4×4像素邻域内的双三次插值）
 - INTER_LANCZOS4 -Lanczos插值（逾8×8像素邻域的Lanczos插值）
- 第六个参数，int类型的borderMode，边界模式，有默认值BORDER_CONSTANT，表示目标图像中“离群点（outliers）”的像素值不会被此函数修改。
- 第七个参数，const Scalar&类型的borderValue，当有常数边界时使用的值，其有默认值Scalar( )，即默认值为0。


### SURF

SURF，我们简单介绍一下，英语全称为SpeededUp Robust Features，直译的话就是“加速版的具有鲁棒性的特征“算法，由Bay在2006年首次提出。SURF是尺度不变特征变换算法（SIFT算法）的加速版。一般来说，标准的SURF算子比SIFT算子快好几倍，并且在多幅图片下具有更好的稳定性。SURF最大的特征在于采用了harr特征以及积分图像的概念，这大大加快了程序的运行时间。SURF可以应用于计算机视觉的物体识别以及3D重构中。

### drawKeypoints函数详解

void drawKeypoints(const Mat&image, const vector<KeyPoint>& keypoints, Mat& outImage, constScalar& color=Scalar::all(-1), int flags=DrawMatchesFlags::DEFAULT )

- 第一个参数，const Mat&类型的src，输入图像。
- 第二个参数，const vector<KeyPoint>&类型的keypoints，根据源图像得到的特征点，它是一个输出参数。
- 第三个参数，Mat&类型的outImage，输出图像，其内容取决于第五个参数标识符falgs。
- 第四个参数，const Scalar&类型的color，关键点的颜色，有默认值Scalar::all(-1)。
- 第五个参数，int类型的flags，绘制关键点的特征标识符，有默认值DrawMatchesFlags::DEFAULT。可以在如下这个结构体中选取值。
