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
- klt_homography_init_添加第二个关键帧: