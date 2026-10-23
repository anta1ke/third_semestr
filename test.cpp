#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <utility>
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

TEST(PersonTest, ConstructorWithExplicitId) {
    const Person p("Сидоров Сидор", "01.01.2000", 42);
    EXPECT_EQ(p.getId(), 42);
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
    const Investigator i("Смирнов Алексей Павлович", "14.05.1975", "майор юстиции", 77);

    EXPECT_EQ(i.getId(), 77);
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
    const CriminalCase c;

    EXPECT_EQ(c.getYear(), 0);
    EXPECT_EQ(c.getInvestigatorId(), 0);
    EXPECT_TRUE(c.getConvictIds().empty());
}

TEST(CriminalCaseTest, GettersAndConvicts) {
    CriminalCase c("Д-1", 2015, "Кража", Article("ст. 158", "Кража"), 5);

    EXPECT_EQ(c.getNumber(), "Д-1");
    EXPECT_EQ(c.getYear(), 2015);
    EXPECT_EQ(c.getContent(), "Кража");
    EXPECT_EQ(c.getArticle().getNumber(), "ст. 158");
    EXPECT_EQ(c.getInvestigatorId(), 5);

    EXPECT_FALSE(c.hasConvict(10));
    c.addConvictId(10);
    c.addConvictId(11);
    EXPECT_TRUE(c.hasConvict(10));
    EXPECT_TRUE(c.hasConvict(11));
    ASSERT_EQ(c.getConvictIds().size(), 2u);
}

TEST(CriminalCaseTest, GetInfoContainsFields) {
    const CriminalCase c("Д-1", 2015, "Кража в магазине", Article("ст. 158", "Кража"), 5);
    const std::string info = c.getInfo();

    EXPECT_NE(info.find("Д-1"), std::string::npos);
    EXPECT_NE(info.find("2015"), std::string::npos);
    EXPECT_NE(info.find("ст. 158"), std::string::npos);
    EXPECT_NE(info.find("Кража в магазине"), std::string::npos);
}

// Вспомогательная функция: архив с тестовыми данными
static Archive makeArchive() {
    Archive archive;
    archive.addPerson(std::make_unique<Investigator>("Смирнов А. П.", "14.05.1975", "майор", 1));
    archive.addPerson(std::make_unique<Investigator>("Кузнецова О. И.", "02.09.1982", "капитан", 2));
    archive.addPerson(std::make_unique<Convict>("Орлов С. Н.", "21.01.1990", "5 лет", 3));
    archive.addPerson(std::make_unique<Convict>("Волков Д. А.", "11.11.1985", "8 лет", 4));

    const Article theft("ст. 158", "Кража");
    const Article fraud("ст. 159", "Мошенничество");

    CriminalCase c1("Д-1", 2015, "Кража из магазина", theft, 1);
    c1.addConvictId(3);
    CriminalCase c2("Д-2", 2018, "Мошенничество с недвижимостью", fraud, 2);
    c2.addConvictId(4);
    CriminalCase c3("Д-3", 2020, "Кража автомобиля, магазин рядом", theft, 1);
    c3.addConvictId(3);
    c3.addConvictId(4);

    archive.addCase(c1);
    archive.addCase(c2);
    archive.addCase(c3);
    return archive;
}

TEST(ArchiveTest, AddPersonRejectsDuplicateIdAndNull) {
    Archive archive;
    archive.addPerson(std::make_unique<Convict>("А", "01.01.2000", "1 год", 100));
    archive.addPerson(std::make_unique<Investigator>("Б", "02.02.2001", "лейтенант", 100));
    archive.addPerson(nullptr);

    EXPECT_EQ(archive.getPeople().size(), 1u);
    EXPECT_EQ(archive.getPeople()[0]->getFullName(), "А");
}

TEST(ArchiveTest, ArticlesAndCasesDeduplication) {
    Archive archive;
    archive.addArticle(Article("ст. 158", "Кража"));
    archive.addArticle(Article("ст. 158", "Кража"));
    archive.addArticle(Article("ст. 159", "Мошенничество"));
    EXPECT_EQ(archive.getArticles().size(), 2u);

    const CriminalCase c("Д-1", 2015, "Описание", Article(), 0);
    archive.addCase(c);
    archive.addCase(c);
    EXPECT_EQ(archive.getCases().size(), 1u);
}

TEST(ArchiveTest, FindPersonById) {
    const Archive archive = makeArchive();

    const Person* p = archive.findPersonById(3);
    ASSERT_NE(p, nullptr);
    EXPECT_EQ(p->getFullName(), "Орлов С. Н.");
    EXPECT_EQ(archive.findPersonById(999), nullptr);
}

TEST(ArchiveTest, Polymorphism) {
    const Archive archive = makeArchive();

    // Итерируем коллекцию как коллекцию базового класса
    int convicts = 0;
    int investigators = 0;
    for (const std::unique_ptr<Person>& p : archive.getPeople()) {
        if (dynamic_cast<const Convict*>(p.get()) != nullptr) {
            convicts++;
            EXPECT_NE(p->getInfo().find("Осужденный"), std::string::npos);
        }
        if (dynamic_cast<const Investigator*>(p.get()) != nullptr) {
            investigators++;
            EXPECT_NE(p->getInfo().find("Следователь"), std::string::npos);
        }
    }
    EXPECT_EQ(convicts, 2);
    EXPECT_EQ(investigators, 2);
}

TEST(ArchiveTest, FindByConvict) {
    const Archive archive = makeArchive();

    const std::vector<const CriminalCase*> found = archive.findByConvict("Орлов С. Н.");
    ASSERT_EQ(found.size(), 2u);
    EXPECT_EQ(found[0]->getNumber(), "Д-1");
    EXPECT_EQ(found[1]->getNumber(), "Д-3");

    EXPECT_EQ(archive.findByConvict("Волков Д. А.").size(), 2u);
    EXPECT_TRUE(archive.findByConvict("Неизвестный").empty());
}

TEST(ArchiveTest, FindByConvictIgnoresInvestigators) {
    const Archive archive = makeArchive();
    EXPECT_TRUE(archive.findByConvict("Смирнов А. П.").empty());
}

TEST(ArchiveTest, FindByInvestigator) {
    const Archive archive = makeArchive();

    const std::vector<const CriminalCase*> found = archive.findByInvestigator("Смирнов А. П.");
    ASSERT_EQ(found.size(), 2u);
    EXPECT_EQ(found[0]->getNumber(), "Д-1");
    EXPECT_EQ(found[1]->getNumber(), "Д-3");

    EXPECT_EQ(archive.findByInvestigator("Кузнецова О. И.").size(), 1u);
    EXPECT_TRUE(archive.findByInvestigator("Орлов С. Н.").empty());
}

TEST(ArchiveTest, FindByContent) {
    const Archive archive = makeArchive();

    EXPECT_EQ(archive.findByContent("магазин").size(), 2u);
    EXPECT_EQ(archive.findByContent("недвижимост").size(), 1u);
    EXPECT_TRUE(archive.findByContent("отсутствует").empty());
    EXPECT_TRUE(archive.findByContent("").empty());
}

TEST(ArchiveTest, FindByArticle) {
    const Archive archive = makeArchive();

    EXPECT_EQ(archive.findByArticle("ст. 158").size(), 2u);
    EXPECT_EQ(archive.findByArticle("Мошенничество").size(), 1u);
    EXPECT_TRUE(archive.findByArticle("ст. 999").empty());
}

TEST(ArchiveTest, GetCaseInfoContainsNames) {
    const Archive archive = makeArchive();

    const std::string info = archive.getCaseInfo(archive.getCases()[2]);
    EXPECT_NE(info.find("Д-3"), std::string::npos);
    EXPECT_NE(info.find("Смирнов А. П."), std::string::npos);
    EXPECT_NE(info.find("Орлов С. Н."), std::string::npos);
    EXPECT_NE(info.find("Волков Д. А."), std::string::npos);
}
