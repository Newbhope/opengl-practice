#version 150 core

layout(points) in;
layout(line_strip, max_vertices = 100) out;

in vec3 vColor[]; //Output from vertex shader for each vertex
in float vLevels[];
in float vBranches[];

out vec3 fColor; //Output to fragment shader

struct stack {
    //initializes to 0 for some reason
    int top;
    vec4 positions[1000];
};

stack treeStack;

void push(vec4 input) {
    treeStack.positions[treeStack.top] = input;
    treeStack.top++;
}

vec4 pop() {
    /*
    if (treeStack.top <= -1) {
        return vec4(0., 0., 0., 0.);
    }
    */
    vec4 result = treeStack.positions[treeStack.top];
    treeStack.top--;
    return result;
}

void main() {
    fColor = vColor[0];

    treeStack.positions[1] = gl_in[0].gl_Position;
    treeStack.top = 1;
    for (int i = 0; i < 100; i++) {
    // while (treeStack.top > -1) {

        vec4 currentPosition = pop();
        gl_Position = currentPosition;
        EmitVertex();

        //left branch
        vec4 leftOffset = vec4(-0.1, 0.1, 0.0, 0.0);
        vec4 leftPoint = currentPosition + leftOffset;
        gl_Position = leftPoint;
        EmitVertex();
        push(leftPoint);

        //move gl_Position back to base of branch
    	gl_Position = currentPosition;
    	EmitVertex();

        //right branch
        vec4 rightOffset = vec4(0.1, 0.1, 0.0, 0.0);
        vec4 rightPoint = currentPosition + rightOffset;
        gl_Position = rightPoint;
        EmitVertex();
        push(rightPoint);
    }

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

	//createSubtree(gl_in[0].gl_Position, vLevels[0]);

    EndPrimitive();
}
