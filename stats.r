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
library(ggplot2)
ggplot(dga, aes(x=SPL)) + geom_histogram(colour="black",fill="#BB7766", binwidth=.5, boundary=0) + labs(title="Average Scrabble Scores per Character, DGA domains") + labs(x="Scrabble Scores per Character") + scale_x_continuous(breaks=seq(0,6,by=1)) + scale_y_continuous(breaks=seq(0,400,by=50))
ggplot(df, aes(x=SPL)) + geom_histogram(colour="black",fill="#6677BB", binwidth=.5, boundary=0) + labs(title="Average Scrabble Scores per Character, Majestic Million") + labs(x="Scrabble Scores per Character") + scale_x_continuous(breaks=seq(0,6,by=1)) + scale_y_continuous(labels = scales::comma)
