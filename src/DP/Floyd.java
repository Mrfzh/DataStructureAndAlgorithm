package DP;

/**
 * Floyd算法
 */
public class Floyd {
    private static final int MAX_INT = 10000;

    public static void main(String[] args) {
        int [][] a = {{0,MAX_INT,3,MAX_INT}, {2,0,MAX_INT,MAX_INT}, {MAX_INT,7,0,1}, {6,MAX_INT,MAX_INT,0}};
        floyd(a);
        print(a);
    }

    /**
     * 输入一个图（加权连通图）的权重矩阵，返回该图的距离矩阵
     *
     * @param a 权重矩阵
     */
    private static void floyd(int [][] a) {
        for (int k = 0; k < a.length; k++) {    //中间顶点数由小到大
            for (int i = 0; i < a.length; i++) {
                for (int j = 0; j < a.length; j++) {
                    if (i != j) {   //如果该点不是到它自己
                        a[i][j] = Math.min(a[i][j], a[i][k] + a[k][j]);
                    }
                }
            }
        }
    }

    private static void print(int [][] a) {
        for (int[] anA : a) {
            for (int anAnA : anA) {
                System.out.print(anAnA);
                System.out.print(" ");
            }
            System.out.print("\n");
        }
    }
}
