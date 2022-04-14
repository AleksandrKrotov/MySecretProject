#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 texCoord;

uniform sampler2D tex0;

void main()
{
   float u_colorFactor = 1.0;
   vec4 sample = texture(tex0, texCoord);
	float grey = 0.21 * sample.r + 0.71 * sample.g + 0.07 * sample.b;
   FragColor = vec4(sample.r * u_colorFactor + grey * (1.0 - u_colorFactor), sample.g * u_colorFactor + grey * (1.0 - u_colorFactor), sample.b * u_colorFactor + grey * (1.0 - u_colorFactor), 1.0);
}