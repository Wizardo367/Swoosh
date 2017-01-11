// Used in IMAT3111

#version 430

in vec3 VertPos;
in vec3 Normal;

uniform vec3 eyePos;
uniform vec4 lightPos;
uniform vec3 lightDirection;
uniform float exponent;
uniform float cutoffU;

uniform vec3 Ka = vec3(0.7f, 1.0f, 0.7f);			// Ambient reflectivity
uniform vec3 Kd = vec3(0.7f, 1.0f, 0.7f);            // Diffuse reflectivity
uniform vec3 Ks = vec3(0.4f);			// Specular reflectivity
uniform vec3 La = vec3(0.4f);			// Ambient light intensity
uniform vec3 Ld = vec3(0.8f);            // Diffuse light intensity

uniform float shininess = 10.f;

layout( location = 0 ) out vec4 FragColour;

vec3 spotlight()
{
	vec3 finalColour; // Return value

	// Calculate angle between the light position and the target position
	vec3 diff = normalize(vec3(lightPos) - VertPos);
	float angle = degrees(acos(dot(-diff, normalize(lightDirection))));
	float cutoff = clamp(cutoffU, 0.0, 90.0); // Limit
	vec3 ambientLight = La * Ka;

	// Check angle
	if (angle < cutoffU)
	{
		// Calculate distance from light source to vertex
		float distance = length(vec3(lightPos) - VertPos);
		// Calculate attenuation
		float dist = 0.01 * distance;
		float attenuation = 1.0 / (0.1 + dist + dist * distance);

		// Diffuse lighting
		float spot = pow(dot(-diff, normalize(lightDirection)), exponent); // Calculate size of spot
		vec3 diffuseLight = spot * Ld * Kd * max(0, dot(normalize(Normal), normalize(-lightDirection)));
	
		// Specular lighting
		vec3 vertexEyeDist = normalize(eyePos - VertPos);
		vec3 lightReflection = normalize(reflect(lightDirection, Normal));
		float specular = dot(vertexEyeDist, lightReflection);
		specular = pow(specular, shininess);

		vec3 specularLight;

		// Check specular
		if (specular > 0)
			specularLight = spot * Ld * Ks * specular;

		// Return final colour
		finalColour = (attenuation * (diffuseLight + specularLight)) + ambientLight;
	}
	else
		finalColour = vec3(0.f, 0.f, 0.f);

	return finalColour;
}

void main() 
{
	FragColour = vec4(spotlight(), 1.0);
}