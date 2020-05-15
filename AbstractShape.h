#pragma once
class AbstractShape
{
public:
	typedef enum ShapeType {
		ABSTRACT,
		CUBOID,
		CYLINDER,
		PRISM,
		PYRAMID,
		SPHERE, 
		ADVANCED
	} ShapeType;

	void set_dimension(double width, double height, double depth);
	void set_width(double);
	void set_height(double);
	void set_depth(double);
	double get_width(void) const;
	double get_height(void) const;
	double get_depth(void) const;
	virtual ShapeType get_shape_type() const;
protected:
	AbstractShape();
	AbstractShape(double, double, double);
	void set_shape_type(ShapeType);
private:
	double width, height, depth;
	ShapeType shape_type = ABSTRACT;
};
