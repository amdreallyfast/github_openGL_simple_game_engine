#version 430
   
in vec4 vert_out_color;
   
out vec4 frag_out_color;
   
void main()
{
   frag_out_color = vert_out_color;
}

