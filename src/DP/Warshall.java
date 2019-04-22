package DP;

/**
 * warshall算法:求有向图的传递闭包
 */
public class Warshall {

    public static void main(String[] args) {
        int [][] a = {{0,1,0,0}, {0,0,0,1}, {0,0,0,0}, {1,0,1,0}};
        warshall(a);
        print(a);
    }

    /**
     * 输入有向图的邻接矩阵，返回该有向图的传递闭包
     * 参考：https://blog.csdn.net/foreverzili/article/details/68481930
     *
     * @param a
     * @return
     */
    private static void warshall(int [][] a) {
        for (int i = 0; i < a.length; i++) {
            for (int j = 0; j < a.length; j++) {
                //对第i列中为1的行进行操作：将该行和第i行进行逻辑或操作，并将结果赋给该行
                if (a[j][i] == 1) {
                    for (int k = 0; k < a.length; k++) {
                        a[j][k] = a[j][k] | a[i][k];
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
