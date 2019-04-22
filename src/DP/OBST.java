package DP;

/**
 * 最优二叉查找树算法
 * 设a1,a2,..,an是从小到大的互不相等的键，p1,p2,...,pn是它们的查找概率
 */
public class OBST {
    public static void main(String[] args) {
        float [] probabilities = {0.1f, 0.2f, 0.4f, 0.3f};
        System.out.println(bestSearchTime(probabilities));
    }

    /**
     * 输入该二叉树各节点的查找概率，返回最优查找时的平均键值比较次数
     *
     * @param probabilities
     * @return
     */
    private static float bestSearchTime(float [] probabilities) {
        int n = probabilities.length;     //键值个数
        float [][] dp = new float[n+2][n+2];    //dp[i][j]表示由ai,...,aj组成的二叉树的最小平均键值比较次数

        //初始条件
        for (int i = 1; i <= n; i++) {
            dp[i][i] = probabilities[i-1];
            dp[i][i-1] = 0;
        }
        dp[n+1][n] = 0;

        for (int len = 1; len < n; len++) {   //计算对角线
            for (int i = 1; i <= n-len; i++) {  //计算dp[i][j]
                int j = i + len;
                float min = dp[i][i-1] + dp[i+1][j];
                float sum = probabilities[i-1];
                for (int m = i+1; m <= j; m++) {
                    if (dp[i][m-1] + dp[m+1][j] < min) {
                        min = dp[i][m-1] + dp[m+1][j];
                    }
                    sum += probabilities[m-1];
                }
                dp[i][j] = min + sum;
            }
        }

        return dp[1][n];
    }
}
