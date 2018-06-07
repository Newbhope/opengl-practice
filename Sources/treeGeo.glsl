#version 150 core

layout(points) in;
layout(line_strip, max_vertices = 100) out;

in vec3 vColor[]; //Output from vertex shader for each vertex
in float vLevels[];
in float vBranches[];

out vec3 fColor; //Output to fragment shader

void createSubtree(in vec4 currentPosition, in int numLevelsLeft) {
	gl_Position = currentPosition;
	EmitVertex();

	//left branch
	vec4 leftOffset = vec4(-0.1, 0.1, 0.0, 0.0);
	gl_Position = currentPosition + leftOffset;
	EmitVertex();

	//move back to base of subtree
	gl_position = currentPosition;
	EmitVertex();

	//right branch
	vec4 rightOffset = vec4(0.1, 0.1, 0.0, 0.0);
	gl_Position = currentPosition + rightOffset;
	EmitVertex();

	if (numLevelsLeft > 0) {
		createSubtree(currentPosition + leftOffset, numLevelsLeft - 1);
		createSubtree(currentPosition + rightOffset, numLevelsLeft + 1);
	}
}

void main() {
    fColor = vColor[0];
	gl_Position = gl_in[0].gl_Position;
	EmitVertex();

    //left branch
    vec4 leftOffset = vec4(-0.1, 0.1, 0.0, 0.0);
    gl_Position = gl_in[0].gl_Position + leftOffset;
    EmitVertex();

	//move current pos back to base of branch
	gl_Position = gl_in[0].gl_Position;
	EmitVertex();

    //right branch
    vec4 rightOffset = vec4(0.1, 0.1, 0.0, 0.0);
    gl_Position = gl_in[0].gl_Position + rightOffset;
    EmitVertex();

	createSubtree(gl_in[0].gl_Position, vLevels[0]);

    EndPrimitive();
}
