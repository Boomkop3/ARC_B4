#include "Pyramid.h"

//					 E
//					 + 
//					/ \`.
//				   /'  \ `. 
//				  /.    \  `.
//			   C /+------\---'+ D
//				/' ` .    \  '
//			   /'      ` . \'
//			A +------------+ B      

Pyramid::Pyramid() : Shape::Shape()
{
	this->set_shape_type(Shape::PYRAMID);
}

Pyramid::Pyramid(double width, double height, double depth) : Shape::Shape(width, height, depth)
{
	this->set_shape_type(Shape::PYRAMID);
}

void Pyramid::get_indices(std::vector<glm::vec3>& vertices_out, std::vector<glm::vec3>& indices_out) const
{
	vertices_out.resize(Pyramid::vertices_count);
	//Vertices
	vertices_out[A] = glm::vec3(-(this->get_width()/2.), -(this->get_height()/2.), this->get_depth()/2.);	 // A
	vertices_out[B] = glm::vec3(this->get_width()/2., -(this->get_height()/2.), this->get_depth()/2.);		 // B
	vertices_out[C] = glm::vec3(-(this->get_width()/2.), -(this->get_height()/2.), -(this->get_depth()/2.)); // C
	vertices_out[D] = glm::vec3(this->get_width()/2., -(this->get_height()/2.), -(this->get_depth()/2.));	 // D
	vertices_out[E] = glm::vec3(this->get_width()/2. / 2, this->get_height()/2., this->get_depth()/2. / 2);  // E

	indices_out.resize(Pyramid::indices_count);
	//ABE
	indices_out[0] = vertices_out[A]; 
	indices_out[1] = vertices_out[B];
	indices_out[2] = vertices_out[E];
	//BDE
	indices_out[3] = vertices_out[B];
	indices_out[4] = vertices_out[D];
	indices_out[5] = vertices_out[E];
	//DCE
	indices_out[6] = vertices_out[D];
	indices_out[7] = vertices_out[C];
	indices_out[8] = vertices_out[E];
	//CAE
	indices_out[9]  = vertices_out[C];
	indices_out[10] = vertices_out[A];
	indices_out[11] = vertices_out[E];
	//ABC
	indices_out[12] = vertices_out[A];
	indices_out[13] = vertices_out[B];
	indices_out[14] = vertices_out[C];
	//DCB
	indices_out[15] = vertices_out[D];
	indices_out[16] = vertices_out[C];
	indices_out[17] = vertices_out[B];
}