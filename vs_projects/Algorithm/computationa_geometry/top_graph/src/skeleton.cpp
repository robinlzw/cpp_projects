#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include "PNG.h"

using namespace std;

#define BLACKPIXEL Pixel(0, 0, 0, 255)

static bool isPixelValid(unsigned int x, unsigned int y, vector<vector<unsigned int>> & v)
{
    return (y >= 0 && y < v.size() && x >= 0 && x < v[0].size());
}

unsigned int getPixelDistance (unsigned int x,
                               unsigned int y,
                               vector<vector<unsigned int>> & distance_map)
{
    if (!isPixelValid(x, y, distance_map))
    {
        return 0;
    }
    return distance_map[y][x];
}

void setPixelDistance (unsigned int x,
                       unsigned int y,
                       unsigned int distVal,
                       vector<vector<unsigned int>> & distance_map)
{
    if (!isPixelValid(x, y, distance_map))
    {
        cout << __FUNCTION__ << ": ERROR could not set pixel distance at x=" << x << " y=" << y << endl;
    }
    distance_map[y][x] = distVal;
}

void getDistanceMap (vector<vector<unsigned int>> & distance_map, PNG & img)
{
    distance_map = vector<vector<unsigned int>>(img.getHeight(), vector<unsigned int>(img.getWidth()));

    // start from top-left corner, moving right and down
    for (int y = 0; y < img.getHeight(); y++)
    {
        for (int x = 0; x < img.getWidth(); x++)
        {
            if (img.getPixel(x, y).approximate(BLACKPIXEL, 100))
            {
                unsigned int minTLDist = min(getPixelDistance(x-1, y, distance_map) + 1,
                                             getPixelDistance(x, y-1, distance_map) + 1);
                setPixelDistance(x, y, minTLDist, distance_map);
                Pixel p(100, 30, 60, 255);
                img.setPixel(x, y, p);
            }
        }
    }

    // start from bottom-right corner, moving left and up
    for (int y = img.getHeight()-1; y >= 0; y--)
    {
        for (int x = img.getWidth()-1; x >= 0; x--)
        {
            if (img.getPixel(x, y).approximate(Pixel(100, 30, 60, 255), 100))
            {
                unsigned int minBRDist = min(getPixelDistance(x+1, y, distance_map) + 1,
                                             min(getPixelDistance(x, y+1, distance_map) + 1,
                                                 distance_map[y][x]));
                setPixelDistance(x, y, minBRDist, distance_map);
                Pixel p(30, 30, 160, 255);
                img.setPixel(x, y, p);
            }
        }
    }

}

void getLocalMaxes (vector<vector<unsigned int>> & distance_map,
                    vector<vector<unsigned int>> & local_maxes)
{	
	if (distance_map.size()) {
		local_maxes = vector<vector<unsigned int>>(distance_map.size(), vector<unsigned int>(distance_map[0].size()));
		//cout << __FUNCTION__ << "distance_map.size() = " << distance_map.size() << ", distance_map[0].size() = " << distance_map[0].size() << endl;
	}
    
    for (int y = 0; y < distance_map.size(); y++)
    {
		// cout << __FUNCTION__ << "distance_map[" << y << "].size()" << distance_map[y].size() << endl;
        for (int x = 0; x < distance_map[y].size(); x++)
        {
            if (distance_map[y][x] != 0 &&
                distance_map[y][x] >= getPixelDistance(x+1,   y, distance_map) &&
                distance_map[y][x] >= getPixelDistance(x+1, y-1, distance_map) &&
                distance_map[y][x] >= getPixelDistance(  x, y-1, distance_map) &&
                distance_map[y][x] >= getPixelDistance(x-1, y-1, distance_map) &&
                distance_map[y][x] >= getPixelDistance(x-1,   y, distance_map) &&
                distance_map[y][x] >= getPixelDistance(x-1, y+1, distance_map) &&
                distance_map[y][x] >= getPixelDistance(  x, y+1, distance_map) &&
                distance_map[y][x] >= getPixelDistance(x+1, y+1, distance_map))
            {
                local_maxes[y][x] = 1;
            }
        }
    }
}

void recreateImage (vector<vector<unsigned int>> & distance_map,
                    vector<vector<unsigned int>> & local_maxes,
                    PNG & img)
{
    if (distance_map.size() == 0 ||
        distance_map.size() != local_maxes.size() ||
        distance_map[0].size() != local_maxes[0].size())
    {
        cout << __FUNCTION__ << ": ERROR distance map and local maxes size mismatch" << endl;
		return;
    }

    vector<vector<vector<bool>>> visited(distance_map.size(),
                                         vector<vector<bool>>(distance_map[0].size(),
                                         vector<bool>(distance_map.size() + distance_map[0].size())));

    for (int y = 0; y < distance_map.size(); y++)
    {
        for (int x = 0; x < distance_map[y].size(); x++)
        {
            if (local_maxes[y][x])
            {
                // cout << "===================processing " << x << "," << y << endl;
                // (x, y), number of steps left
                queue<pair<pair<unsigned int, unsigned int>, unsigned int>> pixel_queue;
                pixel_queue.push({{x, y}, distance_map[y][x]});
                img.setPixel(x, y, BLACKPIXEL);
                while (!pixel_queue.empty())
                {
                    unsigned int currx, curry;
                    unsigned int steps;
                    pair<unsigned int, unsigned int> coordinates;
                    tie(coordinates, steps) = pixel_queue.front();
                    tie(currx, curry) = coordinates;
                    pixel_queue.pop();
                    if (visited[curry][currx][steps]) continue;
                    visited[curry][currx][steps] = true;
                    // cout << currx << "," << curry << " steps: " << steps << endl;

                    if (img.getPixel(currx, curry) != BLACKPIXEL)
                    {
                        img.setPixel(currx, curry, Pixel(255,0,0,255));
                    }

                    if (steps != 0)
                    {
                        if (isPixelValid(currx+1, curry, distance_map) && !visited[curry][currx+1][steps-1])
                        {
                            pixel_queue.push({{currx+1, curry}, steps-1});
                        }
                        if (isPixelValid(currx, curry-1, distance_map) && !visited[curry-1][currx][steps-1])
                        {
                            pixel_queue.push({{currx, curry-1}, steps-1});
                        }
                        if (isPixelValid(currx-1, curry, distance_map) && !visited[curry][currx-1][steps-1])
                        {
                            pixel_queue.push({{currx-1, curry}, steps-1});
                        }
                        if (isPixelValid(currx, curry+1, distance_map) && !visited[curry+1][currx][steps-1])
                        {
                            pixel_queue.push({{currx, curry+1}, steps-1});
                        }
                    }
                }
            }
        }
    }

}

void printDistanceMap (vector<vector<unsigned int>> & distance_map)
{
    for (int y = 0; y < distance_map.size(); y++)
    {
        for (int x = 0; x < distance_map[y].size(); x++)
        {
            if (distance_map[y][x]) cout << distance_map[y][x];
            else cout << " ";
            cout  << ((distance_map[y][x] / 100) ? " "  :
                                           (distance_map[y][x] /  10) ? "  " :
                                                                        "   ");
        // cout << distance_map[y][x] << ((distance_map[y][x] / 100) ? " "  :
        //                                (distance_map[y][x] /  10) ? "  " :
        //                                                             "   ");
        }
        cout << endl;
    }
}

int main () {

    //vector<const char *> filesin = {"../images/apple.png", "../images/batman.png", "../images/discord.png", "../images/cursive.png", "../images/rose.png", "../images/hansolo.png"};
    //vector<const char *> filesout = {"../out/apple.png", "../out/batman.png", "../out/discord.png", "../out/cursive.png", "../out/rose.png", "../out/hansolo.png"};
	vector<const char *> filesin = { "D:/Dev_Cpp/cpp_projects/topGraph/images/apple.png", 
		"D:/Dev_Cpp/cpp_projects/topGraph/images/batman.png",
		"D:/Dev_Cpp/cpp_projects/topGraph/images/discord.png", 
		"D:/Dev_Cpp/cpp_projects/topGraph/images/cursive.png", 
		"D:/Dev_Cpp/cpp_projects/topGraph/images/rose.png", 
		"D:/Dev_Cpp/cpp_projects/topGraph/images/hansolo.png" };
	vector<const char *> filesout = { "D:/Dev_Cpp/cpp_projects/topGraph/out/apple.png", 
		"D:/Dev_Cpp/cpp_projects/topGraph/out/batman.png", 
		"D:/Dev_Cpp/cpp_projects/topGraph/out/discord.png", 
		"D:/Dev_Cpp/cpp_projects/topGraph/out/cursive.png", 
		"D:/Dev_Cpp/cpp_projects/topGraph/out/rose.png", 
		"D:/Dev_Cpp/cpp_projects/topGraph/out/hansolo.png" };

    for (int i = 0; i < filesin.size(); i++)
    {
        PNG img(filesin[i]);
		// cout << __FUNCTION__ << "img.getWidth() = " << img.getWidth() << ", img.getHeight() = " << img.getHeight();
        PNG skeleton(img.getWidth(), img.getHeight());
        PNG recreated(img.getWidth(), img.getHeight());

		cout << "enter for_loop1" << endl;


        vector<vector<unsigned int>> distance_map;
        getDistanceMap(distance_map, img);
		cout << "1.getDistanceMap" << endl;

        vector<vector<unsigned int>> local_maxes;
        getLocalMaxes(distance_map, local_maxes);
		cout << "2.getLocalMaxes" << endl;
		

        for (int y = 0; y < local_maxes.size(); y++)
        {
            for (int x = 0; x < local_maxes[y].size(); x++)
            {
                if (local_maxes[y][x])
                {
                    skeleton.setPixel(x, y, BLACKPIXEL);
                }
            }
        }


        //printDistanceMap(distance_map);
        //printDistanceMap(local_maxes);

        recreateImage(distance_map, local_maxes, recreated);

        // img.write(filesout[i]);
        // skeleton.write(filesout[i]);
        recreated.write(filesout[i]);

		cout << "quit for_loop1" << endl << endl;
    }

	system("pause");

    return 0;
}
