#========================================================================================
# Project: Predicting Heart Disease
# Aim: Accurately Predicting Whether patients of Hospital have AHD
# Model: Classification and Regression Tree & Logistic Regression
# Inputs: Different for both models (Shown below)
# Output: AHD (Yes, No)
# Data/ data source : AHD.csv
# Author: Brandon Chen (bran0025@e.ntu.edu.sg)
# Date: 07.11.2020
#========================================================================================

#-------- Import Data & Libraries --------
library(data.table)
library(nnet)
library(caTools)
library(ggplot2)
library(plotly)
library(rpart)
library(rpart.plot)
library(corrplot)
setwd("/Users/brandonchen/Desktop/NTU/BIZ/BC2406/AY2020sem1 CBA")
ahd.dt <- fread("AHD.csv", stringsAsFactors = TRUE)

#-------- Data Cleaning --------

# Changing binary values '0' and '1' for easier visualization
ahd.dt$Sex <- replace(ahd.dt$Sex, ahd.dt$Sex == 1, "Male" )
ahd.dt$Sex <- replace(ahd.dt$Sex, ahd.dt$Sex == 0, "Female" )
ahd.dt$Fbs <- replace(ahd.dt$Fbs, ahd.dt$Fbs == 1, "True" )
ahd.dt$Fbs <- replace(ahd.dt$Fbs, ahd.dt$Fbs == 0, "False" )
ahd.dt$ExAng <- replace(ahd.dt$ExAng, ahd.dt$ExAng == 1, "Yes" )
ahd.dt$ExAng <- replace(ahd.dt$ExAng, ahd.dt$ExAng == 0, "No" )

# Convert data type of relevant variables to factors
ahd.dt$Sex<-factor(ahd.dt$Sex)
ahd.dt$Fbs<-factor(ahd.dt$Fbs)
ahd.dt$RestECG<-factor(ahd.dt$RestECG)
ahd.dt$ExAng<-factor(ahd.dt$ExAng)
ahd.dt$Slope<-factor(ahd.dt$ Slope)
ahd.dt$Ca<-factor(ahd.dt$ Ca)

# Checking for NA values 
summary(ahd.dt) # Ca and Thal has NA values
ahd.dt[is.na(ahd.dt$Ca)] # View the rows with Ca having NA value
ahd.dt[is.na(ahd.dt$Thal)] # View the rows with Thal having NA value
ahd.dt[ahd.dt$Chol > 500]

# Creating a new column to replace NA values
ahd.dt$numVessels <- ahd.dt$Ca
ahd.dt[is.na(Ca), numVessels:=factor(0)] # Since mode is 0
ahd.dt$Thal2 <- ahd.dt$Thal
ahd.dt[is.na(Thal), Thal2:=factor("normal")]
ahd.dt[is.na(ahd.dt$Ca)] # Check if rows are correctly replaced
ahd.dt[is.na(ahd.dt$Thal)] # Check if rows are correcly replaced

# Dropping actual columns with NA values
ahd.dt = subset(ahd.dt, select = -c(Ca,Thal) )

# View summary
summary(ahd.dt) # Check the rows are corrected



#-------- Data Exploration & Insights --------

# Total number of rows of data
nrow(ahd.dt)
summary(ahd.dt)

# Finding the patients who have AHD
hasAHD.dt <- ahd.dt[AHD == "Yes"]
hasAHD.dt[, AgeGroup := ifelse(Age > 55, 'Above 55', 'Below or Equal to 55')]
hasAHD.dt$AgeGroup <- factor(hasAHD.dt$AgeGroup)
nrow(ahd.dt[ahd.dt$Age>55]) # 152 AHD Patients above Age 55

# Figure 1 & 2: More males tend to contract AHD and they contract it at an earlier age than females
ggplot(hasAHD.dt, aes(Sex, fill=Sex)) + geom_bar() + ggtitle("Gender Proportion Among AHD Patients") + theme(plot.title = element_text(hjust = 0.5, face = "bold"))
ggplot(hasAHD.dt, aes(Age)) + geom_density(aes(fill=Sex), alpha=0.8) + ggtitle("Distribution Of AHD Patients Across Age") + theme(plot.title = element_text(hjust = 0.5, face = "bold"))
nrow(hasAHD.dt[hasAHD.dt$Sex == "Male"]) # 114 Patients
nrow(hasAHD.dt[hasAHD.dt$Sex == "Female"]) # 25 Patients

# Figure 3: Female AHD Patients have higher RestBP compared to any other categories
ggplot(ahd.dt, aes(AHD, RestBP, fill = Sex)) + geom_boxplot() + facet_grid( ~ Sex, scales="free") + ylab("Resting Blood Pressure") + xlab("Does Patient Has AHD?") + ggtitle("Comparing Resting Blood Pressure Between Gender") + theme(plot.title = element_text(hjust = 0.5, size = 12, face = "bold"))

# Figure 4: Most of AHD Patients have Asymptomatic Chest Pain and are above the Age of 55
ggplot(hasAHD.dt, aes(ChestPain, fill=AgeGroup)) + geom_bar(position = "stack") + ggtitle("Types of Chest Pain Among AHD Patients") + theme(plot.title = element_text(hjust = 0.5))
nrow(hasAHD.dt[hasAHD.dt$ChestPain == "asymptomatic"]) # 105 Patients who are Asymptomatic
nrow(hasAHD.dt[hasAHD.dt$ChestPain != "asymptomatic"]) # 34 Patients who experienced Chest Pain
nrow(hasAHD.dt[hasAHD.dt$ChestPain == "asymptomatic" & hasAHD.dt$Age > 55]) # 65 Asymptomatic AHD Patients above age 55
nrow(hasAHD.dt[hasAHD.dt$ChestPain == "asymptomatic" & hasAHD.dt$Age <= 55]) # 40 Asymptomatic AHD Patients above age 55

# Figure 5: Maximum Heart Rate Across Age of Patients
ggplot(ahd.dt, aes(Age,MaxHR,color=AHD)) + geom_point() + geom_smooth(method=lm, se=FALSE) + ggtitle("Maximum Heart Rate Across Age of Patients") + theme(plot.title = element_text(hjust = 0.5))
ggplotly() # Identifying MaxHR for each point
ahd.dt[ahd.dt$MaxHR == 71] # Patient who has sgnificantly lower MaxHR compared to rest

# Additional Figure: Cholesterol Levels generally increase slightly across age
ggplot(ahd.dt, aes(Age,Chol,color=AHD)) + geom_jitter() + geom_smooth(method=lm, se=FALSE) + ggtitle("Maximum Heart Rate Across Age of Patients") + theme(plot.title = element_text(hjust = 0.5))
ggplotly() # Identifying Outlier
ahd.dt[ahd.dt$Chol == 564] # Patient who has sgnificantly higher Cholesterol compared to rest

#-------- Logistic Regression Predictions --------

# Initial Logistic Regression Analysis
set.seed(2019)
levels(ahd.dt$AHD) # Baseline is "No"
log.m1 <- glm(AHD ~ ., family = binomial,data = ahd.dt)
summary(log.m1) # Sex, ChestPain, numVessels, Slope identified to be strongest significance

# Train-Test Split (Ratio of Trainset:Testset is 70:30)
set.seed(2019)
train <- sample.split(Y = ahd.dt$AHD, SplitRatio = 0.7)
trainset <- subset(ahd.dt, train == T)
testset <- subset(ahd.dt, train == F)
summary(trainset$AHD) # Ensure trainset has the same proportion as initial dataset
summary(testset$AHD) # Ensure testset has the same proportion as initial dataset

# Retrain a logistic model
train_AHD <- glm(AHD ~ Sex+ChestPain+numVessels+Slope, family = binomial,data = trainset) 
summary(train_AHD)

# VIF
vif(train_AHD) # Variables are not multicollinear

# Odds Ratio and OR Confidence Interval
OR <- exp(coef(train_AHD))
OR
OR.CI <- exp(confint(train_AHD))
OR.CI # Range does not include 1

# Output the probability from the logistic function for Trainset
predict_AHD_train <- predict(train_AHD, type="response")  
threshold <- sum(ahd.dt$AHD == "Yes")/length(ahd.dt$AHD) # Set the threshold for predicting AHD = 'Yes' based on probability
train_hat <- ifelse(predict_AHD_train > threshold, "Yes", "No") # Predict Y = "Yes" if probability > threshold, else predict Y = "No".
table(Trainset.Actual = trainset$AHD, train_hat, deparse.level = 2) # Confusion matrix.
mean(train_hat == trainset$AHD) # Trainset Accuracy of 0.8207547

# Output the probability from the logistic function for Testset
predict_AHD_test <- predict(train_AHD, newdata = testset,type="response")
test_hat <- ifelse(predict_AHD_test > threshold, "Yes", "No")
log_cm <- table(Testset.Actual = testset$AHD, test_hat, deparse.level = 2) 
mean(test_hat == testset$AHD) # Accuracy of 0.7692308

# Other Model Performance Metrics
TP = log_cm[2,2]
TN = log_cm[1,1]
FN = log_cm[1,2]
FP = log_cm[2,1]
round((TP+TN)/sum(TP,FP,TN,FN), 2)
sensitivity = round(TP / (TP + FN), 2)
sensitivity # Sensitivity of 0.73
specificity = round(TN / (TN + FP), 2)
specificity # Specificity of 0.80


#-------- CART Model Predictions --------
set.seed(2019)
cart1 <- rpart(AHD ~ ., data = trainset,
               method = 'class', control = rpart.control(minsplit = 20, cp = 0))
printcp(cart1) # cp table
plotcp(cart1) # cp graph

# Finding the optimal CP value
CVerror.cap <- cart1$cptable[which.min(cart1$cptable[,"xerror"]), "xerror"] +
  cart1$cptable[which.min(cart1$cptable[,"xerror"]), "xstd"]
i <- 1; j<- 4
while (cart1$cptable[i,j] > CVerror.cap) {i <- i + 1}
cp.opt = ifelse(i > 1, sqrt(cart1$cptable[i,1] * cart1$cptable[i-1,1]), 1)
cp.opt

# Pruning the CART Model using optimal CP
cart2 <- prune(cart1, cp = cp.opt)
rpart.plot(cart2, nn= T, main = "Pruned Tree")

# Output the variable importance of the CART model
cart2$variable.importance
try_cart <- cart2$variable.importance[]
round(prop.table(try_cart)*100,0)

# Model Predictions
Predicted_AHD <- predict(cart2, newdata = testset,type="class")
summary(Predicted_AHD)

# Confusion Matrix
cart_cm<-table(Actual_AHD = testset$AHD, Predicted_AHD, deparse.level = 2)
cart_cm

# Accuracy of CART Model
mean(Predicted_AHD == testset$AHD) # Accuracy of 0.8241758

# Other Model Performance Metrics
TP.cart = cart_cm[2,2]
TN.cart = cart_cm[1,1]
FN.cart = cart_cm[1,2]
FP.cart = cart_cm[2,1]
sensitivity.cart = round(TP.cart / (TP.cart + FN.cart), 2)
sensitivity.cart # Sensitivty of 0.81
specificity.cart = round(TN.cart / (TN.cart + FP.cart), 2)
specificity.cart # Specificity of 0.84

#-------- CART Model Predictions with Surrogates --------
# import same file
extra.dt <- fread("AHD.csv", stringsAsFactors = TRUE)

# Changing binary values '0' and '1' for easier visualization
extra.dt$Sex <- replace(extra.dt$Sex, extra.dt$Sex == 1, "Male" )
extra.dt$Sex <- replace(extra.dt$Sex, extra.dt$Sex == 0, "Female" )
extra.dt$Fbs <- replace(extra.dt$Fbs, extra.dt$Fbs == 1, "True" )
extra.dt$Fbs <- replace(extra.dt$Fbs, extra.dt$Fbs == 0, "False" )
extra.dt$ExAng <- replace(extra.dt$ExAng, extra.dt$ExAng == 1, "Yes" )
extra.dt$ExAng <- replace(extra.dt$ExAng, extra.dt$ExAng == 0, "No" )

# Convert data type of relevant variables to factors
extra.dt$Sex<-factor(extra.dt$Sex)
extra.dt$Fbs<-factor(extra.dt$Fbs)
extra.dt$RestECG<-factor(extra.dt$RestECG)
extra.dt$ExAng<-factor(extra.dt$ExAng)
extra.dt$Slope<-factor(extra.dt$ Slope)
extra.dt$Ca<-factor(extra.dt$ Ca)

# Same Train-Test Split (Ratio of Trainset:Testset is 70:30)
set.seed(2019)
extra_train <- sample.split(Y = extra.dt$AHD, SplitRatio = 0.7)
extra_trainset <- subset(extra.dt, extra_train == T)
extra_testset <- subset(extra.dt, extra_train == F)
summary(extra_trainset$AHD) # Ensure trainset has the same proportion as initial dataset
summary(extra_testset$AHD) # Ensure testset has the same proportion as initial dataset

# Performing CART Model Predictions again
set.seed(2019)
extra_cart <- rpart(AHD ~ ., data = extra_trainset,
               method = 'class', control = rpart.control(minsplit = 20, cp = 0))
printcp(extra_cart)
plotcp(extra_cart)

# Finding the optimal CP value
CVerror.cap <- extra_cart$cptable[which.min(extra_cart$cptable[,"xerror"]), "xerror"] +
  extra_cart$cptable[which.min(extra_cart$cptable[,"xerror"]), "xstd"]
i <- 1; j<- 4
while (extra_cart$cptable[i,j] > CVerror.cap) {i <- i + 1}
cp.opt = ifelse(i > 1, sqrt(extra_cart$cptable[i,1] * extra_cart$cptable[i-1,1]), 1)
cp.opt

# Pruning the CART Model using optimal CP
extra_cart2 <- prune(extra_cart, cp = cp.opt)
rpart.plot(extra_cart2, nn= T, main = "Pruned Tree")

# Output the variable importance of the CART model
extra_cart2$variable.importance

# Model Predictions
Extra_Predicted_AHD <- predict(extra_cart2, newdata = extra_testset,type="class")
summary(Extra_Predicted_AHD)

# Confusion Matrix
cart2_cm<-table(Actual_AHD = extra_testset$AHD, Extra_Predicted_AHD, deparse.level = 2)
cart2_cm

# Accuracy of CART Model
mean(Extra_Predicted_AHD == extra_testset$AHD) # Accuracy of 0.8571429

# Other Model Performance Metrics
TP.cart2 = cart2_cm[2,2]
TN.cart2 = cart2_cm[1,1]
FN.cart2 = cart2_cm[1,2]
FP.cart2 = cart2_cm[2,1]
sensitivity.cart2 = round(TP.cart2 / (TP.cart2 + FN.cart2), 2)
sensitivity.cart2 # Sensitivity of 0.87
specificity.cart2 = round(TN.cart2 / (TN.cart2 + FP.cart2), 2)
specificity.cart2 # Specificity of 0.85

