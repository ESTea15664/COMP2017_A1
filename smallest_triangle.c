#include<stdio.h>
#include<math.h>
#include<string.h>

// get perimeter of triangle(or not) formed by three points
float get_perm(float pts[3][2]){
    float side_length = 0;
    float get_length();

    for (int i = 0; i < 3; i++){
        side_length += get_length(pts[i], pts[i+1]);
    }

    return side_length;
}

// get the length between two floats
float get_length(float pt1[2], float pt2[2]){
    float del_X = pt1[0] - pt2[0];
    float dex_Y = pt1[1] - pt2[1];

    float length = sqrtf((del_X * del_X) + (dex_Y * dex_Y));

    return length;
}

// determin if any three given points forms a triangle
// note: tried comparing the length of the longest line and the sum of two others, 
//       which always returns "is" for some reason
char * is_triangle(float pts[3][2]){
    float area = 
    (pts[0][0] * (pts[1][1] - pts[2][1])) + 
    (pts[1][0] * (pts[0][1] - pts[2][1])) + 
    (pts[2][0] * (pts[0][1] - pts[1][1]));

    if (area == 0) return "is not";
    else return "is";
}

int main(void){
    // initialize attributes to store points
    char buffer[100];
    float pts[100][2];

    // a helpful int to record the number of points
    int numOPts = 0;

    // reading points from stdin
    for (int i = 0; (fgets(buffer, sizeof(buffer), stdin)) != NULL; i++){
        if (strlen(buffer) != 1){
            sscanf(buffer, "%f, %f", &pts[i][0], &pts[i][1]);
            numOPts = i + 1;

            continue;
        }
        break;
    }

    // ignore numOPts < 3
    if (numOPts < 3){
        return 0;
    }

    // initialize attributes to get triangles
    float tri_pts[numOPts][3][2];

    // filter out three closest points
    // first loop: get initial point 
    for (int i = 0; i < numOPts; i++){
        float tri_pt[3][2] = {{pts[i][0], pts[i][1]}, {0, 0}, {0, 0}};

        // second loop: get 1st closest point
        int clst_index = 0;
        float dist = 142;
        for (int j = 0; j < numOPts; j++){
            // ignore repeated points
            if (pts[j] == pts[i]){
                continue;
            }
            else if (get_length(pts[i], pts[j]) < dist){
                dist = get_length(pts[i], pts[j]);

                tri_pt[1][0] = pts[j][0];
                tri_pt[1][1] = pts[j][1];

                clst_index = j;
            }
            else continue;
        }

        // third loop: get 2nd closest point
        dist = 142;
        for (int k = 0; k < numOPts; k++){
            // ignore same point
            if (pts[k] == pts[i] || pts[k] == pts[clst_index]){
                continue;
            }
            else if (get_length(pts[i], pts[k]) < dist){
                dist = get_length(pts[i], pts[k]);

                tri_pt[2][0] = pts[k][0];
                tri_pt[2][1] = pts[k][1];
            }
            else continue;
        }

        // forth loop assign value to tri_pts
        for (int x = 0; x < 3; x++){
            tri_pts[i][x][0] = tri_pt[x][0];
            tri_pts[i][x][1] = tri_pt[x][1];
        }
    }

    // get perimeter from all triangles and find the smallest one
    float perm = 242;

    int sml_index = 0;

    for (int i = 0; i < numOPts; i++){
        if (get_perm(tri_pts[i]) < perm){
            perm = get_perm(tri_pts[i]);
            sml_index = i;
        }
    }

    float smlst[3][2] = {
        {tri_pts[sml_index][0][0], tri_pts[sml_index][0][1]}, 
        {tri_pts[sml_index][1][0], tri_pts[sml_index][1][1]}, 
        {tri_pts[sml_index][2][0], tri_pts[sml_index][2][1]}
    };

    // result printing
    printf("read %d points\n", numOPts);

    for (int i = 0; i < 3; i++){
        printf("%f, %f\n", smlst[i][0], smlst[i][1]);
    }

    printf("This %s a triangle\n", is_triangle(smlst));

    return 0;
}