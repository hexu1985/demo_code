

/**
 * @brief 数学工具类
 */
class MathTools {
public:
	/**
	 * @brief 计算两点\f$(x_1,y_1)\f$和\f$(x_2,y_2)\f$之间的距离:
	 *			\f$\sqrt{(x_2-x_1)^2+(y_2-y_1)^2}\f$
	 *
	 * @param x1 \f$x_1\f$
	 * @param y1 \f$y_1\f$
	 * @param x2 \f$x_2\f$
	 * @param y2 \f$y_2\f$
	 *
	 * @return \f$\sqrt{(x_2-x_1)^2+(y_2-y_1)^2}\f$
	 */
	double distance(double x1, double y1, double x2, double y2);

	/**
	 * @brief 打印函数
	 */
	void print();

};
