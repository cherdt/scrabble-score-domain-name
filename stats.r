library(plyr)

# read in our tab-delimited files as R data frames
mm <- read.table("majestic_stats.txt", header=TRUE)
dga <- read.table("dga_stats.txt", header=TRUE)

# Some basic summary stats
max(mm$SCORE)
min(mm$SCORE)
mean(mm$SCORE)
median(mm$SCORE)
sd(mm$SCORE)

# Even better, the summary function
summary(mm)
summary(dga)

# You can filter the data frame to get a summary of subsets of data
summary(mm[mm$SCORE >= 50,])
summary(dga[dga$SCORE >= 50,])

# Histograms are helpful for visualizing the data
hist(dga$SPL, freq=TRUE, xlim=range(0, 10), col="#BB7766", border="black", main="Average Scrabble Score per Character, DGA Domains", xlab="Average Scrabble Score per Character", ylab="Count")
hist(df$SPL, freq=TRUE, xlim=range(0, 10), col="#6677BB", border="black", main="Average Scrabble Score per Character, Majestic Million", xlab="Average Scrabble Score per Character", ylab="Count")

# What if we want more ticks/labels on the x-axis?
hist(df$SPL, freq=TRUE, xlim=range(0, 10), col="#6677BB", border="black", main="Average Scrabble Score per Character, Majestic Million", xlab="Average Scrabble Score per Character", ylab="Count", axis(1, at=seq(1,10,by=1), label=seq(1,10,by=1)))

# What if we want to scale the y-axis? Good question!
# Another option is to use the ggplot2 library
# This site was very helpful: https://dereksonderegger.github.io/570L/9-graphing-using-ggplot2.html
library(ggplot2)
ggplot(dga, aes(x=SPL)) + geom_histogram(colour="black",fill="#BB7766", binwidth=.5, boundary=0) + labs(title="Average Scrabble Scores per Character, DGA domains") + labs(x="Scrabble Scores per Character") + scale_x_continuous(breaks=seq(0,6,by=1)) + scale_y_continuous(breaks=seq(0,400,by=50))
ggplot(df, aes(x=SPL)) + geom_histogram(colour="black",fill="#6677BB", binwidth=.5, boundary=0) + labs(title="Average Scrabble Scores per Character, Majestic Million") + labs(x="Scrabble Scores per Character") + scale_x_continuous(breaks=seq(0,6,by=1)) + scale_y_continuous(labels = scales::comma)

# We have a really long tail on the total Scrabble scores for the Majestic Million
# We can chop it off with xlim(0,100) but we lose data for 151 domains (0.015%)
ggplot(df, aes(x=SCORE)) + geom_histogram(colour="black",fill="#6677BB", binwidth=1, boundary=0) + labs(title="Scrabble Scores, Majestic Million") + labs(x="Scrabble Scores") + xlim(0,100) + scale_y_continuous(labels = scales::comma)

# Logistic regression
# First, import a set of all domains (Majestic Million and DGAs), sorted randomly.
# There must be a column to identify DGAs (0 or 1)
combined <- read.csv("combined_stats_ml.csv", header=TRUE)

# Split it into a training set and a test set
train <- combined[1:700000,]
test <- combined[-(1:700000)]

# Create a linear regression model
model <- glm(DGA~SCORE+LENGTH+SPL+ENTROPY+EPL,family=binomial(link='logit'),data=train)

# Get summary data about the model
summary(model)

# Add ROCR library
library(ROCR)

# Predict which items in the test set are DGAs
# The demo used a different way to subset data, which appears to be the same:
# p <- predict(model, newdata=subset(test,c(SCORE,LENGTH,SPL,ENTROPY,EPL)), type="response")
p <- predict(model, newdata=test[,3:7], type="response")

# Create a prediction object based on the prediction data
pr <- prediction(p, test$DGA)

# Create a performance object with measures for true positive rate and false positive rate
prf <- performance(pr, measure="tpr", x-measure="fpr")

# Graph it
plot(prf)

# Get the Area Under the Curve (AUC)
auc <- performance(pr, measure="auc")

# Principal Components Analysis (PCA)
# https://www.datacamp.com/community/tutorials/pca-analysis-r
pc <- prcomp(combined[,c(3:7)], center=TRUE, scale=TRUE)
summary(pc)

# Plot it. Don't you just love installing unknown code from GitHub
library(devtools)
install_github("vqv/ggbiplot")
library(ggbiplot)
ggbiplot(pc)

# Well, that plot is useless. This one is slightly more interesting
ggbiplot(pc, groups=df$DGA, ellipse=TRUE, varname.size = 5)


