import open3d as o3d
import numpy as np
import json
import time

direction_color = [1, 0.5, 1]

label_index_dict = {
    'Car': 0, 'car': 0,
    'Cyclist': 1, 'bicycle': 1,
    'Pedestrian': 2, 'pedestrian': 2,
    'Fence': 3, 'fence': 3,
    'Truck': 4, 'truck': 4,
    'bus': 5,
    'tricycle': 6,
    'TrafficCone': 7, 'cone': 7,
}
index_color_map = {
    '0': [0, 1, 0],  # green [0, 1, 0]
    '1': [0, 1, 1],  # cyan [0, 1, 1]
    '2': [1, 1, 0],  # yellow [1, 1, 0]
    '3': [1, 0, 0],  # red [1, 0, 0]
    '4': [1, 0, 1],  # pink [1, 0, 1]
    '5': [0.5, 0.5, 0],  # little yellow
    '6': [0.5, 0.5, 1],  # little blue
    '7': [0, 0, 1],  # blue [0, 0, 1]
}

lines_box = np.array([[0, 1], [1, 3], [3, 2], [2, 0],
                      [4, 5], [5, 7], [7, 6], [6, 4],
                      [0, 4], [1, 5], [2, 6], [3, 7]])


def rotz(theta):
    c = np.cos(theta)
    s = np.sin(theta)
    return np.array([
        [c, -s, 0],
        [s, c, 0],
        [0, 0, 1]
    ])


def get_3d_box_and_direction(box):
    # x, y, z, length, width, height, phi, psi, angle
    x, y, z, length, width, height, theta = box[:7]
    R = rotz(theta)
    x_conners = [length / 2, length / 2, -length / 2, -length / 2, length / 2, length / 2, -length / 2, -length / 2]
    y_conners = [width / 2, -width / 2, width / 2, -width / 2, width / 2, -width / 2, width / 2, -width / 2]
    z_conners = [height / 2, height / 2, height / 2, height / 2, -height / 2, -height / 2, -height / 2, -height / 2]
    # # show 1
    # conners_3d = np.dot(R, np.vstack([x_conners, y_conners, z_conners]))
    # show 2
    x_conners = np.array(x_conners).reshape(-1, 1)
    y_conners = np.array(y_conners).reshape(-1, 1)
    z_conners = np.array(z_conners).reshape(-1, 1)
    points = np.concatenate((x_conners, y_conners, z_conners), axis=1)
    conners_3d = np.dot(points, R)
    conners_3d = np.transpose(conners_3d)

    conners_3d[0, :] = conners_3d[0, :] + x
    conners_3d[1, :] = conners_3d[1, :] + y
    conners_3d[2, :] = conners_3d[2, :] + z
    conners_3d = np.transpose(conners_3d)

    dir_x = (conners_3d[0][0] + conners_3d[1][0]) / 2
    dir_y = (conners_3d[0][1] + conners_3d[1][1]) / 2
    direction_3d = np.array([[x, y, z], [dir_x, dir_y, z]])

    return conners_3d, direction_3d


def pcd_view(files_list, fps=1, dilate=1, only_view=True, view_gt=False, view_gt_select=False, remove_object=False):
    # 创建窗口对象
    vis = o3d.visualization.Visualizer()
    # 设置窗口标题
    window_name = "pred"
    if view_gt:
        window_name = "anno"
    if view_gt_select:
        window_name = "anno_select"
    vis.create_window(window_name=window_name)
    # 设置点云大小
    vis.get_render_option().point_size = 1
    # 设置颜色背景为黑色
    opt = vis.get_render_option()
    opt.background_color = np.asarray([0, 0, 0])

    num_total = len(files_list)
    for _, predict_file in enumerate(files_list):
        # print("%d/%d" % (_, num_total), predict_file)
        with open(predict_file) as file:
            predict_dict = json.load(file)

        geometries = []
        if not remove_object:
            try:
                raw_point = np.array(predict_dict['points4d'])[:, :3]  # 读取1.npy数据  N*[x,y,z]
            except:
                print("points not points4d")
                raw_point = np.array(predict_dict['points'])[:, :3]  # 读取1.npy数据  N*[x,y,z]
        else:
            raw_point = np.array(predict_dict['points_after_remove'])[:, :3]  # 读取1.npy数据  N*[x,y,z]
        # 创建点云对象
        pcd = o3d.open3d.geometry.PointCloud()
        # 将点云数据转换为Open3d可以直接使用的数据类型
        mask = [True if max(point) < 40 and min(point) > -40 else False for point in raw_point]
        raw_point = raw_point[mask]
        pcd.points = o3d.open3d.utility.Vector3dVector(raw_point)
        # 设置点的颜色为白色
        pcd.paint_uniform_color([1, 1, 1])
        # 将点云加入到窗口中
        geometries.append(pcd)  # vis.add_geometry(pcd)

        boxes = predict_dict['pred_boxes']  # 读取boxes.npy数据  x, y, z, length, width, height, angle
        labels = predict_dict['pred_names']
        if view_gt:
            boxes = predict_dict['anno_boxes']
            labels = predict_dict['anno_names']
        if view_gt_select:
            boxes = predict_dict['anno_boxes_select']
            labels = predict_dict['anno_names_select']

        # if not (3 in labels or 4 in labels):
        #     continue
        print("%d/%d" % (_, num_total), predict_file)

        boxes_3d = []
        direction_3d = []
        for idx, box in enumerate(boxes):
            box, direction = get_3d_box_and_direction(box)
            boxes_3d.append(box)
            direction_3d.append(direction)
        boxes_3d = np.array(boxes_3d)  # N * 8 * 3
        direction_3d = np.array(direction_3d)  # N * 2 * 3

        for idx, points_3dbox in enumerate(boxes_3d):  # 8 * [x,y,z] （八个顶点的空间信息）

            label = labels[idx]
            try:
                label = label_index_dict[label]
            except:
                pass
            label_color = index_color_map[str(label)]

            # 指明哪两个顶点之间相连
            global lines_box
            # 设置点与点之间线段的颜色
            colors = np.array([label_color for _ in range(len(lines_box))])
            # 创建Bbox候选框对象
            line_set = o3d.geometry.LineSet()
            # 将八个顶点连接次序的信息转换成o3d可以使用的数据类型
            line_set.lines = o3d.utility.Vector2iVector(lines_box)
            # 设置每条线段的颜色
            line_set.colors = o3d.utility.Vector3dVector(colors)
            # 把八个顶点的空间信息转换成o3d可以使用的数据类型
            line_set.points = o3d.utility.Vector3dVector(points_3dbox)
            # 将矩形框加入到窗口中
            geometries.append(line_set)  # vis.add_geometry(line_set)

        for idx, points_3ddirection in enumerate(direction_3d):  # 2 * [x,y,z] （2个顶点的空间信息）
            # 指明哪两个顶点之间相连
            lines_box_direction = np.array([[0, 1]])
            # 设置点与点之间线段的颜色
            colors = np.array([direction_color for _ in range(len(lines_box_direction))])
            # 创建Bbox候选框对象
            line_set = o3d.geometry.LineSet()
            # 将八个顶点连接次序的信息转换成o3d可以使用的数据类型
            line_set.lines = o3d.utility.Vector2iVector(lines_box_direction)
            # 设置每条线段的颜色
            line_set.colors = o3d.utility.Vector3dVector(colors)
            # 把八个顶点的空间信息转换成o3d可以使用的数据类型
            line_set.points = o3d.utility.Vector3dVector(points_3ddirection)
            # 将矩形框加入到窗口中
            geometries.append(line_set)  # vis.add_geometry(line_set)

        for g in geometries:
            vis.add_geometry(g)
        vis.get_view_control().set_zoom(1 / dilate)

        if only_view:
            vis.run()
            vis.update_renderer()
            vis.clear_geometries()
            # time.sleep(1 / fps)
            time.sleep(0.1)
        else:
            vis.poll_events()
            vis.update_renderer()
            vis.clear_geometries()
            # time.sleep(1 / fps)
            time.sleep(0.1)

    vis.destroy_window()


def copy_files():
    import os, shutil
    scene_times_dict = {
        # "062": ["0:20:2", "20:40:5", "46:50:2"],
        # "063": ["1:20:2", "20:22:1", "25:38:2", "58:59:1"],
        # "064": ["0:1:1", "6:8:1", "11:12:1", "19:24:1", "27:28:1"],
        # "065": ["6:8:1", "12:17:1"],
        # "067": ["6:8:1", "14:27:2"],
        # "068": ["6:8:1", "20:29:1", "32:33:1", "41:47:1", "55:58:1", "72:83:2", "88:90:1", "93:98:1"],
        # "069": ["2:4:1", "6:8:1", "15:16:1", "19:20:1", "35:36:1", "44:45:1"],

        # "xt15002": ["0:81:3"],
        # "xt15003": ["30:90:3", "95:96:1"],
        # "xt15004": ["0:20:2", "20:90:8", "90:91:1", "96:97:1", "110:130:3", "130:132:1"],
        # "xt15005": ["25:55:2", "61:65:1"],
        # "xt15007": ["9:14:1", "38:41:1", "130:145:2"],
        # "xt15014": ["0:16:2", "73:77:1", "110:140:5", "140:148:1"],
        # "xt15015": ["16:120:10"],
    }
    scene_list = list(scene_times_dict.keys())
    scene_list.sort()
    for scene in scene_list:
        scene_soot = os.path.join("D:\\data\\pcd_remove_object\\06", scene)
        target_soot = os.path.join("E:\\000_labelcloud\\03predict\\", scene)
        assert not os.path.exists(target_soot)
        os.mkdir(target_soot)

        name_list = os.listdir(scene_soot)
        name_list.sort()

        index_list = []
        for times in scene_times_dict[scene]:
            start, end, step = map(int, times.split(":"))
            end = len(name_list) if end == -1 else end
            index_list += list(range(start, end, step))

        for index in index_list:
            name = name_list[index]
            source_path = os.path.join(scene_soot, name)
            target_path = os.path.join(target_soot, name)
            shutil.copy(source_path, target_path)

        print(len(index_list), scene_soot)
        print(len(os.listdir(target_soot)), len(index_list), len(index_list) == len(os.listdir(target_soot)), target_soot)


def main_view():
    import os
    # predict_root = 'E:\\000_labelcloud\\03predict\\xt15015'
    # predict_root = 'D:\\data\\view_predict\\mop05'
    # predict_root = 'D:\\data\\pcd_remove_object\\tmp'
    #predict_root = '.'
    #names = os.listdir(predict_root)
    # names = [name for name in names if "tb004" in name]

    #names.sort()
    #predict_list = [os.path.join(predict_root, name) for name in names]
    #print("predict_list len:", len(predict_list))
    pcd_view(["./clip_1001_1689834399790__1689836880.699942_1689836880.699450.json"], dilate=2)
    # 077 0,
    # tb 1 17, 2 51, 3 65, 4 82, 5 92, 6 119, 7 129, 8 136, 9 150, 10 164
    #    11 191, 12 205, 13 255, 14 269, 15 279, 16 313,
    # xt 1 333, 4 343, 5 367, 6 387, 7 408, 8 428, 9 448,
    #    11 455, 13 475, 14 482, 16 489, 17 506, 18 533, 19 540, 20 554,
    #    21 564, 22 581, 23588, 24 598, 25 625, 26 635, 27 658, 28 675, 29692, 30 706,
    #    31 720, 32 734, 33 754, 35 791, 36 805, 37 819, 38 839, 39 866, 40 873,
    #    41 904, 42 924


    # pcd_view([predict_list[1]], dilate=5, remove_object=False)

"""
062 0:20:2(loc), 20:40:5(duo), 46:50:2(duo)                                 16
063 1:20:2(loc&duo), 20:22:1, 25:38:2, 58:59:1                              20
064 （复制第一帧）0:1:1, 6:8:1, 11:12:1, 19:24:1, 27:28:1                     10
065 6:8:1, 12:17:1                                                          7
067 6:8:1, 14:27:2                                                          9
068 6:8:1, 20:29:1, 32:33:1, 41:47:1, 55:58:1, 72:83:2, 88:90:1, 93:98:1    34
069 2:4:1, 6:8:1, 15:16:1, 19:20:1, 35:36:1, 44:45:1                        8
                                                                            104
"""
"""
# xt15006 130::2  # 点云消失，严重漏检
# xt15002 :81:3(tricycle)
# xt15003 30:90:3, 95:96:1
# xt15004 0:20:2, 1:22:2, 20:90:8(duo), 90:91:1, 96:97:1(duo), 110:130:3(bus), 130:132:1
# xt15005 25:55:2, 61:67:1
# xt15007 9:14:1, 38:41:1, 130:145:2, 131:141:2
# xt15014 0:16:2, 3:7:2, 73:77:1, 110:140:5(duo), 140:148:1
# xt15015 16:120:10(duo)
"""
if __name__ == '__main__':
    main_view()
    # copy_files()
