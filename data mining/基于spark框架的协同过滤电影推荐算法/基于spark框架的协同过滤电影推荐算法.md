# 基于spark框架的协同过滤电影推荐算法

### 阮正鑫 120032910012

### 1、算法原理

​       众所周知，协同过滤（Collaboration Filtering）算法是推荐系统中最常用的一种算法。今天我们就以电影推荐为例，简要论述基本原理，最终给出实现的python代码。

####  1.1、 问题描述

​       我们可以假设有一个表格，记录着每个用户对所看电影的评分情况，以下图为例：

![img](https://img-blog.csdn.net/20180109145713269)

​       从图中可以看出，该表记录了4个用户对五部电影的评分情况，其中部分数据缺失，即用户没有对这部电影做出评分。推荐系统所需要完成的工作就是根据表格已有的信息对缺失值进行填充，实际的功能就是根据用户喜好和电影特征来评估该用户对该电影的评分情况。

​       为完成这个目标，我们需要做两项工作。一个是对用户的喜好进行评价，二是对电影的特征进行评价。我们将从两个方面展开说明。

#### 1.2、用户喜好描述

​       假设已知每部电影具有两个特征$x^{(1)}$、$x^{(2)}$，其中$x^{(1)}$表示该电影浪漫的程度，$x^{(2)}$表示该电影搞笑的程度。如果一部电影的特征表示为$(1,0)$，那么就认为该电影是一部爱情浪漫片；如果特征表示为$(0,1)$，那么就认为该电影是一部喜剧片；如果表示为$(0.6,0.5)$，那么就认为该电影是一部爱情浪漫喜剧片。

​       如果现在已经通过手工标记，计算出所有电影的特征数据，那么我们就可以利用这些数据来学习每个用户的喜好了。由于电影特征x是二维的，用户喜好θ也应该是二维的。如果学习到Alice的用户喜好$\theta$为$(4.5,1)$，而《cute puppies of love》这部电影的特征为$(0.9,0)$，那么就可以评估Alice对《cute puppies of love》的评分为4.05。该评分在现实中是合理的，Alice的用户喜好特征表明她喜欢爱情片，《cute puppies of love》的特征表明它是一部爱情片，因此评分也就较高。下面将给出数学化描述。   

​       对于每一个用户而言，优化目标为：
$$
J^{(j)}=\min_{\theta^{(j)}}{\frac{1}{2m^{(j)}}\sum_{i:r(i,j)=1}{((\theta^{（j）})^T}x^{(i)}-y^{(i,j)})^2+\frac{\lambda}{2m^{(j)}}\sum_{k=1}^{n}{(\theta^{(j)}_k)^2}}
$$

​       其中$\theta^{（j）}$表示第$j$个用户的爱好特征，$x^{(i)}$表示第$i$部电影的特征，$y^{(i,j)}$表示第$j$个用户对第$i$部电影的评分，$i:r(i,j)=1$表示第$j$个用户对第$i$部电影是评了分的，$m^{(j)}$表示第$j$个用户评分电影的数目。右侧那一项为正则项，是防止过拟合的。由于左右两项具有$m^{(j)}$，因此上式还可以写成：
$$
J^{(j)}=\min_{\theta^{(j)}}{\frac{1}{2}\sum_{i:r(i,j)=1}{((\theta^{（j）})^T}x^{(i)}-y^{(i,j)})^2+\frac{\lambda}{2}\sum_{k=1}^{n}{(\theta^{(j)}_k)^2}}
$$
​       接着，利用梯度下降更新$\theta^{(j)}$:
$$
\theta^{(j)}=\theta^{(j)}-\alpha[\sum_{i:r(i,j)=1}{((\theta^{（j）})^T}x^{(i)}-y^{(i,j)})x^{(i)}+\lambda\sum_{k=1}^{n}{(\theta^{(j)}_k)}]
$$
​      最终所求$\theta^{(j)}$即为第$j$个用户的喜好特征

#### 1.3、电影特征描述

​       如果是已知用户喜好$\theta$，那么我们就可以学习电影的特征$x$了。对于每一部电影，其优化函数为:
$$
J^{(i)}=\min_{x^{(i)}}{\frac{1}{2}\sum_{j:r(i,j)=1}{((\theta^{（j）})^T}x^{(i)}-y^{(i,j)})^2+\frac{\lambda}{2}\sum_{k=1}^{n}{(x^{(i)}_k)^2}}
$$
​       接着，利用梯度下降更新$x^{(i)}$:
$$
x^{(i)}=x^{(i)}-\alpha[\sum_{j:r(i,j)=1}{((\theta^{（j）})^T}x^{(i)}-y^{(i,j)})(\theta^{（j）})^T+\lambda\sum_{k=1}^{n}{(x^{(i)}_k)}]
$$
​      最终所求$x^{(i)}$即为第$i$部电影的特征。

#### 1.4、特征描述结合

​       如果现在电影特征和用户喜好特征都未知，我们可以把上面两个目标函数结合起来进行优化。如下图所示

![img](https://img-blog.csdn.net/20180109161510266)

​       因此，可以得出如下协同过滤算法：

![img](https://img-blog.csdn.net/20180109163149613)

​       最终，我们可以得到用户喜好和电影特征。根据训练得到的这些参数，我们就可以预测那些缺失值了，然后就可以把那些预测的高分电影推荐给用户了。

### 2、算法实现

​       明确协同过滤的算法原理后，我们基于spark框架在python下实现该算法。pyspark中设计了接口实现协同过滤算法，我们通过调用该接口，运用网上提供的电影评价数据集，进行模型的训练。并在测试集上进行测试，实现向用户推荐新的影片。

​       调用pyspark下mllib库中的函数，进行协同过滤模型训练

```python
from pyspark.mllib.recommendation import ALS

def train_model(training, num_iterations=10, rank=1, lambda_=0.01):
    return ALS.train(training.rdd, iterations=num_iterations, rank=rank, lambda_=lambda_, seed=0)
```

​       设计参数调优函数，对以上模型训练的参数进行调整。

```python
def tuning_model(training, test):
    testing = test.select(["userId", "movieId"]).rdd

    min_mse = 1e6
    best_rank = 10
    best_lambda = 1.0
    num_iterations = 10
    for rank in range(1, 5):
        for lambda_f in range(1, 5):
            lambda_ = lambda_f * 0.01
            asl = train_model(training, num_iterations, rank, lambda_)
            predictions = asl.predictAll(testing).toDF(["userId", "movieId", "p_rating"])
            rates_and_preds = test \
                .join(predictions,[test.userId == predictions.userId, test.movieId == predictions.movieId]) \
                .drop(test.userId).drop(test.movieId)

            MSE = rates_and_preds.rdd.map(lambda r: (r.rating - r.p_rating) ** 2) \
                      .reduce(lambda x, y: x + y)/rates_and_preds.count()
            print ("rank = %s, lambda = %s, Mean Squared Error = %s" % (rank, lambda_, MSE))

            if MSE < min_mse:
                min_mse = MSE
                best_rank = rank
                best_lambda = lambda_

    return train_model(training, num_iterations, best_rank, best_lambda)
```

​       运用训练完成的模型，实现对用户的推荐

```python
def recommend_for_all(model, movies, result_path, file_out_flag=False):
    def parse_recommendations(line):
        res = []
        for item in line[1]:
            movie_name = b_movies.value[item[1]]
            res.append((movie_name, float(item[2])))
        return Row(user=line[0], recommendations=res)

    b_movies = spark.sparkContext.broadcast(dict((int(l[0]), l[1]) for l in movies.collect()))
    products_for_all_users = model.recommendProductsForUsers(10).map(parse_recommendations).toDF()
    recommendation_result = products_for_all_users.repartition(1).orderBy(products_for_all_users.user).rdd \
        .map(lambda l: Row(str(l.user) + "," + str(list((r[0], r[1]) for r in l.recommendations))))\
        .toDF().repartition(1)
    if file_out_flag:  # 输出到文件
        recommendation_result.write.text(result_path)
```

​    完整代码以及训练数据在附件中随附。

