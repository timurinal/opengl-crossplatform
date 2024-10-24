#version 430 core

out vec3 finalColour;

in vec3 fragColour;

void main() {
    finalColour = vec3(fragColour);
}