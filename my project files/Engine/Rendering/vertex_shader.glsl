#version 430
	
in layout(location = 0) vec4 vert_in_position;
//in layout(location = 1) vec4 vert_in_color;

out vec4 vert_out_color;

void main()
{
   gl_Position = vert_in_position;

   vert_out_color = vec4(1.0f, 0.0f, 0.0f, 1.0f);//vert_in_color;
}

