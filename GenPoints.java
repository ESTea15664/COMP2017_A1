import java.util.Random;

public class GenPoints {
    // set max absolute values of X and Y
    int maxAbsX = 50;
    int maxAbsY = 50;

    public static void main(String[] args) {
        int[] arg_values = new GenPoints().format_arg(args);

        new GenPoints().Generate(
                arg_values[0], arg_values[1], arg_values[2]
        );

    }

    public void Generate(int minDist, int N, int rSeed){
        // initial condition pass
            // N < 0
        if (N < 0){
            System.err.println("N less than zero");
            System.exit(1);
        }

            // minDist < 0 or minDist > 10
        if (minDist < 0 || minDist > 10){
            System.err.println("mindist outside range");
            System.exit(-2);
        }

            // point saturation
        if (N > (10000 / (Math.PI * minDist * minDist))){
            System.err.println("point saturation");
            System.exit(-3);
        }

        // set up random
        Random random = new Random(rSeed);
        double X;
        double Y;

        double[][] points = new double[N][2];

        for (int i = 0; i < N; i++){
            // define point coordinates
            X = random.nextDouble() * (2 * maxAbsX) - maxAbsX;
            Y = random.nextDouble() * (2 * maxAbsY) - maxAbsY;

            // boolean for checking distance between points
            boolean fitDist = true;
            for (double[] point : points) {
                if (point == null){
                    break;
                }
                else if (get_Distance(X, Y, point[0], point[1]) < minDist) {
                    fitDist = false;
                    break;
                }
            }

            if (fitDist){
                points[i][0] = (double) Math.round(X * 100) / 100;
                points[i][1] = (double) Math.round(Y * 100) / 100;
            }
        }

        for (double[] point: points){
            System.out.println(point[0] + ", " + point[1]);
        }
    }

    public static double get_Distance(double p1X, double p1Y, double p2X, double p2Y){
        return Math.sqrt((p1X - p2X)*(p1X - p2X) + (p1Y - p2Y)*(p1Y - p2Y));
    }

    public int[] format_arg(String[] args){
        // initialized with -1s, for detecting missing arguments
        int[] values = {-1, -1, -1};

        // placing corresponding values in place
        for (String s: args) {
            String[] arg = s.split("=");
            if (arg[0].equals("-mindist")){
                values[0] = Integer.parseInt(arg[1]);
            }
            else if (arg[0].equals("-N")){
                values[1] = Integer.parseInt(arg[1]);
            }
            else if (arg[0].equals("-rseed")){
                values[2] = Integer.parseInt(arg[1]);
            }
        }

        // missing arguments
        for (int i: values){
            if (i == -1){
                System.err.println("invalid arguments");
                System.exit(-4);
            }
        }
        return values;
    }
}