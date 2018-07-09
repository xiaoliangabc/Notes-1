# rpg_svo阅读笔记
## [SVO源码链接](https://github.com/uzh-rpg/rpg_svo)
------
## 类介绍
### KltHomographyInit:
- 该类利用最开始的两个关键帧的Homography初始化初始位姿
- [关于Homography的介绍](https://blog.csdn.net/heyijia0327/article/details/53782094)
- FramePtr frame_ref_;              //!< 参考帧
- vector<cv::Point2f> px_ref_;      //!< keypoints to be tracked in reference frame.
- vector<cv::Point2f> px_cur_;      //!< tracked keypoints in current frame.
- vector<Vector3d> f_ref_;          //!< bearing vectors corresponding to the keypoints in the reference image.
- vector<Vector3d> f_cur_;          //!< bearing vectors corresponding to the keypoints in the current image.
- vector<double> disparities_;      //!< disparity between first and second frame.
- vector<int> inliers_;             //!< inliers after the geometric check (e.g., Homography).
- vector<Vector3d> xyz_in_cur_;     //!< 3D points computed during the geometric check.
- SE3 T_cur_from_ref_;              //!< computed transformation between the first two frames.

### Frame
- static int frame_counter_:记录被创建的帧的数量
- int id_:                  每一个帧的id号
- double timestamp_:        帧被拍下的时间
- vk::AbstractCamera* cam_: 相机模型
- Sophus::SE3 T_f_w_:       Transform (f)rame from (w)orld.
- Matrix<double, 6, 6> Cov_:Covariance.
- ImgPyr img_pyr_:          图像金字塔,typedef vector<cv::Mat> ImgPyr;
- Features fts_:            图像的特征点的list,typedef list<Feature*> Features;
- vector<Feature*> key_pts_:5个特征点和他们对应的空间中的3D点,用来检测是否两帧有重叠
- bool is_keyframe_:        标志位，记录是否是关键帧
- g2oFrameSE3* v_kf_:       Temporary pointer to the g2o node object of the keyframe.
- int last_published_ts_:   上一次publishing的时间戳

### FastDetector : AbstractDetector
- const int cell_size_:
- const int n_pyr_levels_;
- const int grid_n_cols_;
- const int grid_n_rows_;
- vector<bool> grid_occupancy_;
- Corner
  - int x;
  - int y;
  - int level:Corner的pyramid level
  - float score:Corner的shi-tomasi score
  - float angle:for gradient-features: dominant gradient angle.
- Feature
  - FeatureType type;     //!< Type can be corner or edgelet.
  - Frame* frame;         //!< Pointer to frame in which the feature was detected.
  - Vector2d px;          //!< Coordinates in pixels on pyramid level 0.
  - Vector3d f;           //!< Unit-bearing vector of the feature.
  - int level;            //!< Image pyramid level where feature was extracted.
  - Point* point;         //!< Pointer to 3D point which corresponds to the feature.
  - Vector2d grad;        //!< Dominant gradient direction for edglets, normalized.

### Map : boost::noncopyable
- list< FramePtr > keyframes_;          //!< List of keyframes in the map.
- list< Point* > trash_points_;         //!< A deleted point is moved to the trash bin. Now and then this is cleaned. One reason is that the visualizer must remove the points also.
- MapPointCandidates point_candidates_;

### Reprojector
- Options
  - size_t max_n_kfs(10);         //!< max number of keyframes to reproject from
  - bool find_match_direct(true);
- size_t n_matches_;
- size_t n_trials_;
- Candidate:记录了一个特征点的世界坐标和像素坐标
  - Point* pt;                    //!< 3D point.
  - Vector2d px;                  //!< projected 2D pixel location.
- Grid grid_                      
  - CandidateGrid cells;          //cells=vector<cell>,每个cell类似于Grid下面的一个小房间,每个小房间里面有一个list<Candidate>.
  - vector<int> cell_order;
  - int cell_size;
  - int grid_n_cols;
  - int grid_n_rows;
- Matcher matcher_;
- Map& map_;
------
## 流程
### processFirstFrame(处理第一帧)
- 初始化位姿:new_frame_->T_f_w_=单位阵
- klt_homography_init_添加第一个关键帧:
  - 检测特征
    - 提取第一帧中的特征点,记录特征点的像素坐标(2d)px_ref_,归一化平面的坐标(3d)f_ref_
    - 如果特征点<100,失败，重新输入第一帧
  - 初始化KltHomographyInit.frame_ref
  - 在KltHomographyInit.px_cur_.begin()前插入px_ref_
  - 返回成功
- 设置该帧为关键帧,从该帧的特征点中提取了5个关键特征点key_pts_，分布图片的5个角落，用来检测两帧是否有重叠
- 将该关键帧插入地图
- stage_ = STAGE_SECOND_FRAME,用于状态机跳转
### processSecondFrame(处理第二帧)
- klt_homography_init_添加第二个关键帧:
  - trackKlt对第一帧和第二帧进行光流追踪
    - calcOpticalFlowPyrLK(frame_ref, frame_cur, px_ref, px_cur, status, error)//此时的px_cur_和px_ref_是一样的
        - frame_ref:第一帧
        - frame_cur:第二帧
        - px_ref:第一帧的特征点的像素坐标
        - px_cur:第二帧的特征点的像素坐标
        - status:匹配情况,vector类型,status[0]=1就代表第一对px_ref和px_cur的匹配正常；否则不正常
        - error:每对匹配的误差
    - 根据status删除不正常的匹配点
    - 计算disparities:每对匹配点的像素误差
  - 如果匹配到的特征点对的个数<设定值,返回FAILURE
  - 如果disparities平均值<设定值,返回NO_KEYFRAME
  - computeHomography(f_ref, f_cur, focal_length, reprojection_threshold, inliers, xyz_in_cur, T_cur_from_ref)
    - f_ref:参考帧特征点的归一化坐标
    - f_cur:当前帧特征点的归一化坐标
    - focal_length:相机的焦距fx
    - reprojection_threshold:人为设定的值
    - inliers:有效数据,计算H阵后，利用H阵将图1上的特征点投影到图2,然后用投影结果和图2真实的特征点位置计算残差，若第n对匹配点的残差小于某值，则inlier.push_back(n).所以inlier记录了哪些点对是有效匹配的
    - xyz_in_cur:第一帧特征点的空间位置
    - T_cur_from_ref:SE3类型的数据,前两帧之间的位姿变换矩阵
    - 构造Homography类,计算H矩阵,分解H矩阵(这个过程有点复杂),最终求得位姿变换矩阵T_c2_from_c1,包含R和T信息
    - computeInliers(f_cur, f_cur, R, T, reprojection_threshold, focal_length, xyz_in_cur, inliers, outliers)
      - outliers: 无效数据,与inliers相对
    - T_cur_from_ref = Homography.T_c2_from_c1
  - 如果inlier.size <设定值，返回失败
  - 计算xyz_in_cur.z的平均值scene_depth_median,就是第一幅图特征点的平均空间深度
  - scale = 1/scene_depth_median:这里的1代表机器人初始化被平移1米
  - Rescale the map such that the mean scene depth is equal to the specified scale
    - frame_cur->T_f_w_ = T_cur_from_ref_ * frame_ref_->T_f_w_;
    - frame_cur->T_f_w_.translation() = -frame_cur->T_f_w_.rotation_matrix()*(当前帧世界坐标 + scale*(当前帧世界坐标 - 前一帧世界坐标));
  - 上一步操作没太懂，反正是根据平均深度更新了frame_cur->T_f_w_.translation()这个变量
  - 根据inliers,将每一对有效匹配的点对,计算出其世界坐标(每一对点只有一个世界坐标)
  - 根据世界坐标,构建Feature类型的特征点
  - 将这些特征点都add到frame_cur和frame_ref中
  - 返回成功
- 设置该帧为关键帧,从该帧的特征点中提取了5个关键特征点key_pts_，分布图片的5个角落，用来检测两帧是否有重叠
- 获取该帧的平均和最小深度
- 深度滤波器插入关键帧
- 将该关键帧插入地图
- stage_ = STAGE_DEFAULT_FRAME,用于状态机跳转
- klt_homography_init_.reset
### processFrame(处理第后续帧)
- 初始化当前帧的位姿:new_frame_->T_f_w_ = last_frame_->T_f_w_;
- 构建SparseImgAlign类,用于利用重投影的方法优化位姿
  - SE3 T_cur_from_ref(cur_frame_->T_f_w_ * ref_frame_->T_f_w_.inverse());
  - 优化T_cur_from_ref
  - cur_frame_->T_f_w_ = T_cur_from_ref * ref_frame_->T_f_w_
  - 返回跟踪到的特征点数
- 地图重投影
  - 遍历map里保存的关键帧，如果某个关键帧中的5个key_pts_在当前帧视野范围内,就把该关键帧add进close_kfs容器
  - close_kfs是pair类型,close_kfs.first是对应的关键帧,close_kfs.second是关键帧与当前帧的位姿差异=(frame->T_f_w_的变换矩阵-kf->T_f_w_的变换矩阵).norm
  - 根据close_kfs.second对close_kfs中的关键帧进行排序
  - 将最靠近当前帧的N帧存入overlap_kfs_容器中,overlap_kfs_.first是关键帧,overlap_kfs_.second记录了该关键帧帧有多少特征点在当前帧的视野中
  - 调用Reprojector::reprojectPoint将特征点根据其像素坐标的位置存入grid_.cells;每个cell里面有一个list<Candidate>,每个list记录了一个特征点的世界坐标和像素坐标.
    - 我的理解:对于每个cell,虽然里面有一条list的候选特征点,但只选其中一个来匹配,这样可以避免匹配的特征点都集中在画面的某个区域,使得匹配的点对均匀分布在整个画面
  - 对map_.point_candidates_也执行reprojectPoint操作,如果某一个point_candidates在10帧里都没有出现在视野内,就剔除它
  - 遍历所有的grid.cells,在每个cell中选一个特征点进行匹配
    - 对cell中的候选点,根据点的质量指标进行排序
    - 这边没看懂
  - 记录下匹配成功的特征点的个数
  - 如果匹配到的点的个数不够多
    - new_frame_->T_f_w_ = last_frame_->T_f_w_; //reset to avoid crazy pose jumps
    - tracking_quality_ = TRACKING_INSUFFICIENT;
    - 返回失败
- 位姿优化
  - 遍历当前帧的特征点fts_,计算投影误差e=project2d(特征点归一化平面3d坐标)-project2d(frame->T_f_w_ * 特征点世界坐标)
  - 根据特征点的金字塔层级去缩放e，层级越高，e越小。比如level=2，e=e*1/100
  - errors.push_back(e.norm());
  - estimates scale by computing the median absolute deviation(上面的errors)
  - 开始优化,优化次数人为设定
    - 遍历当前帧的特征点fts_,计算总残差
    - 利用ldlt求解方程Ax=b;A,b已知,x未知
      - A: J.transpose * J
      - b: J.transpose * e
      - Ax=b其实就是:J * dT = e;注意这里的J是误差相对于位姿的雅各布矩阵,所以算出来的dT其实就是一个最优微小扰动,使得e变为0
      - 之所以要在前面乘J.transpose是为了让A变成方阵,这样可以SVD分解
    - 从第二轮优化开始,如果新的误差比上一次优化后的误差大,就让frame->T_f_w_ = T_old;很简单,优化了反而误差大了,不如不优化
    - 更新:
      - T_new = SE3::exp(dT)*frame->T_f_w_; 
      - T_old = frame->T_f_w_; 
      - frame->T_f_w_ = T_new;
      - 不能直接frame->T_f_w_ = SE3::exp(dT)*frame->T_f_w_;因为这是矩阵运算,这么搞会出错的
    - 如果误差<设定值,直接退出优化
  - 更新frame->Cov_
  - 把当前帧重投影误差比较大的几个特征点fts_删掉
  - 如果优化完之后剩下的fts_个数<20,返回失败
- 结构优化,优化路标点的位姿


  
