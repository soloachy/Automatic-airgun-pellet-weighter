# Automatic-airgun-pellet-weighter
The codebase of the current automatic pellet weighting system i have at home 

# Credits 
Bogdan necula HX711 library https://github.com/bogde/HX711

# Disclaimer
this code is pretty specific for my structure and my components so take it just as an example and as proof that something like this can be done,

# Really important disclaimer 
this code is really janky and for some reason the program sometimes does not load or doesn't work properly 
it might be an hardware issue on my part

# Components

i used a load cell from a scale used in jewelry and a ADC converter,an HX711, to get arduino to read the values, 
the range where the measurements have an approx 80% accuracy is centigrams; i haven't been able to measure accurately the milligrams;
i think because of hardware limitations: like arduino's limitate resolution, airflow,
inaccuraccy of the servomotors and electromagnetic interferences.

I STRONGLY suggest that you reduce as much as possible the surface of the weighting pan and cover it with a box to ensure no air flow.

# other

i've provided the original 3D fusion 360 files and the splices with whom i made the structure, beware i had to modify it with other pieces in my workshop.

