#include <gtest/gtest.h>

#include <functional>
#include <stdexcept>
#include <string>
#include <vector>

#include "../lib/include/Archive.h"
#include "../lib/include/Person.h"
#include "../lib/include/Convict.h"
#include "../lib/include/Investigator.h"
#include "../lib/include/Article.h"
#include "../lib/include/CriminalCase.h"

TEST(PersonTest, Getters) {
    const Person p("Иванов Иван Иванович", "12.03.1985");

    EXPECT_GT(p.getId(), 0);
    EXPECT_EQ(p.getFullName(), "Иванов Иван Иванович");
    EXPECT_EQ(p.getBirthDate(), "12.03.1985");
}

TEST(PersonTest, GetInfo) {
    const Person p("Иванов Иван Иванович", "12.03.1985");
    const std::string info = p.getInfo();

    EXPECT_NE(info.find("Иванов Иван Иванович"), std::string::npos);
    EXPECT_NE(info.find("12.03.1985"), std::string::npos);
    EXPECT_NE(info.find("ID:"), std::string::npos);
}

TEST(PersonTest, DefaultConstructorHasValidId) {
    const Person p;
    EXPECT_GT(p.getId(), 0);
}

TEST(PersonTest, AutoIdsAreUnique) {
    const Person a("А", "01.01.2000");
    const Person b("Б", "01.01.2000");
    EXPECT_NE(a.getId(), b.getId());
}

TEST(ConvictTest, GettersAndInfo) {
    const Convict c("Орлов Сергей Николаевич", "21.01.1990", "5 лет лишения свободы");

    EXPECT_EQ(c.getFullName(), "Орлов Сергей Николаевич");
    EXPECT_EQ(c.getSentence(), "5 лет лишения свободы");
    EXPECT_NE(c.getInfo().find("Осужденный"), std::string::npos);
    EXPECT_NE(c.getInfo().find("5 лет лишения свободы"), std::string::npos);
}

TEST(InvestigatorTest, GettersAndInfo) {
    const Investigator i("Смирнов Алексей Павлович", "14.05.1975", "майор юстиции");

    EXPECT_GT(i.getId(), 0);
    EXPECT_EQ(i.getRank(), "майор юстиции");
    EXPECT_NE(i.getInfo().find("Следователь"), std::string::npos);
    EXPECT_NE(i.getInfo().find("майор юстиции"), std::string::npos);
}

TEST(ArticleTest, GettersAndToString) {
    const Article a("ст. 158", "Кража");

    EXPECT_EQ(a.getNumber(), "ст. 158");
    EXPECT_EQ(a.getTitle(), "Кража");
    EXPECT_EQ(a.toString(), "ст. 158 (Кража)");
}

TEST(CriminalCaseTest, DefaultIsZeroInitialized) {
    const
