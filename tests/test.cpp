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
    const Archive archive;
    const Article a(archive, "ст. 158", "Кража");

    EXPECT_EQ(a.getNumber(), "ст. 158");
    EXPECT_EQ(a.getTitle(), "Кража");
    EXPECT_EQ(a.toString(), "ст. 158 (Кража)");
}

TEST(ArticleTest, ConstructorThrowsIfNumberExists) {
    Archive archive;
    archive.addArticle(Article(archive, "ст. 158", "Кража"));

    EXPECT_THROW(Article(archive, "ст. 158", "Другое название"), std::invalid_argument);
    EXPECT_NO_THROW(Article(archive, "ст. 159", "Мошенничество"));
}

TEST(CriminalCaseTest, DefaultIsZeroInitialized) {
    const CriminalCase c;

    EXPECT_EQ(c.getYear(), 0);
    EXPECT_EQ(c.getInvestigatorId(), 0);
    EXPECT_TRUE(c.getConvictIds().empty());
}

// Тестовый класс: архив с тестовыми данными
class ArchiveTest : public ::testing::Test {
    protected:
        Archive archive;   // объявлен первым: статьи ниже создаются с проверкой по нему
        const Investigator smirnov{"Смирнов А. П.", "14.05.1975", "майор"};
        const Investigator kuznetsova{"Кузнецова О. И.", "02.09.1982", "капитан"};
        const Convict orlov{"Орлов С. Н.", "21.01.1990", "5 лет"};
        const Convict volkov{"Волков Д. А.", "11.11.1985", "8 лет"};
        const Article theft{archive, "ст. 158", "Кража"};
        const Article fraud{archive, "ст. 159", "Мошенничество"};

        ArchiveTest() {
            archive.addInvestigator(smirnov);
            archive.addInvestigator(kuznetsova);
            archive.addConvict(orlov);
            archive.addConvict(volkov);
            archive.addArticle(theft);
            archive.addArticle(fraud);

            CriminalCase c1(archive, "Д-1", 2015, "Кража из магазина", theft, smirnov.getId());
            c1.addConvictId(archive, orlov.getId());
            archive.addCase(c1);

            CriminalCase c2(archive, "Д-2", 2018, "Мошенничество с недвижимостью", fraud, kuznetsova.getId());
            c2.addConvictId(archive, volkov.getId());
            archive.addCase(c2);

            CriminalCase c3(archive, "Д-3", 2020, "Кража автомобиля, магазин рядом", theft, smirnov.getId());
            c3.addConvictId(archive, orlov.getId());
            c3.addConvictId(archive, volkov.getId());
            archive.addCase(c3);
        }
};

// CriminalCase: проверки в конструкторе и addConvictId

TEST_F(ArchiveTest, CaseGetters) {
    const CriminalCase c(archive, "Д-9", 2021, "Описание", theft, smirnov.getId());

    EXPECT_EQ(c.getNumber(), "Д-9");
    EXPECT_EQ(c.getYear(), 2021);
    EXPECT_EQ(c.getContent(), "Описание");
    EXPECT_EQ(c.getArticle().getNumber(), "ст. 158");
    EXPECT_EQ(c.getInvestigatorId(), smirnov.getId());
    EXPECT_TRUE(c.getConvictIds().empty());
}

TEST_F(ArchiveTest, CaseGetInfoContainsFields) {
    const CriminalCase c(archive, "Д-9", 2021, "Кража в магазине", theft, smirnov.getId());
    const std::string info = c.getInfo();

    EXPECT_NE(info.find("Д-9"), std::string::npos);
    EXPECT_NE(info.find("2021"), std::string::npos);
    EXPECT_NE(info.find("ст. 158"), std::string::npos);
    EXPECT_NE(info.find("Кража в магазине"), std::string::npos);
}

TEST_F(ArchiveTest, CaseConstructorThrowsIfNumberExists) {
    EXPECT_THROW(CriminalCase(archive, "Д-1", 2021, "Тот же номер", theft, smirnov.getId()), std::invalid_argument);
}

TEST_F(ArchiveTest, CaseConstructorThrowsIfInvestigatorNotFound) {
    EXPECT_THROW(CriminalCase(archive, "Д-9", 2021, "Описание", theft, 999), std::invalid_argument);
}

TEST_F(ArchiveTest, CaseConstructorThrowsIfConvictGivenAsInvestigator) {
    // ID есть в архиве, но это осужденный, а не следователь
    EXPECT_THROW(CriminalCase(archive, "Д-9", 2021, "Описание", theft, orlov.getId()), std::invalid_argument);
}

TEST_F(ArchiveTest, AddConvictIdChecksConvict) {
    CriminalCase c(archive, "Д-9", 2021, "Описание", theft, smirnov.getId());

    EXPECT_THROW(c.addConvictId(archive, 999), std::invalid_argument);                 // нет такого
    EXPECT_THROW(c.addConvictId(archive, kuznetsova.getId()), std::invalid_argument);  // это следователь

    c.addConvictId(archive, orlov.getId());
    EXPECT_THROW(c.addConvictId(archive, orlov.getId()), std::invalid_argument);       // уже добавлен
    ASSERT_EQ(c.getConvictIds().size(), 1u);
    EXPECT_TRUE(c.hasConvict(orlov.getId()));
}

// Archive

TEST(ArchiveBasicTest, AddSameConvictTwiceThrows) {
    const Convict a("А", "01.01.2000", "1 год");

    Archive archive;
    archive.addConvict(a);
    EXPECT_THROW(archive.addConvict(a), std::invalid_argument);

    ASSERT_EQ(archive.getConvicts().size(), 1u);
    EXPECT_EQ(archive.getConvicts()[0].getFullName(), "А");
}

TEST(ArchiveBasicTest, AddSameInvestigatorTwiceThrows) {
    const Investigator b("Б", "02.02.2001", "лейтенант");

    Archive archive;
    archive.addInvestigator(b);
    EXPECT_THROW(archive.addInvestigator(b), std::invalid_argument);
    EXPECT_EQ(archive.getInvestigators().size(), 1u);
}

TEST(ArchiveBasicTest, ArchiveStoresCopies) {
    Archive archive;
    {
        const Convict temp("Временный", "01.01.2000", "1 год");
        archive.addConvict(temp);
    }   // temp уничтожен, но в архиве лежит его копия
    ASSERT_EQ(archive.getConvicts().size(), 1u);
    EXPECT_EQ(archive.getConvicts()[0].getFullName(), "Временный");
}

TEST(ArchiveBasicTest, AddSameArticleTwiceThrows) {
    Archive archive;
    const Article a(archive, "ст. 158", "Кража");
    archive.addArticle(a);
    EXPECT_THROW(archive.addArticle(a), std::invalid_argument);
    EXPECT_EQ(archive.getArticles().size(), 1u);
    EXPECT_TRUE(archive.hasArticle("ст. 158"));
    EXPECT_FALSE(archive.hasArticle("ст. 159"));
}

TEST(ArchiveBasicTest, EmptyArchiveHasNoPeople) {
    const Archive archive;
    EXPECT_FALSE(archive.hasConvict(1));
    EXPECT_FALSE(archive.hasInvestigator(1));
    EXPECT_THROW(archive.findConvictById(1), std::out_of_range);
    EXPECT_THROW(archive.findInvestigatorById(1), std::out_of_range);
}

TEST_F(ArchiveTest, AddSameCaseTwiceThrows) {
    // дело создано, пока номера Д-9 в архиве не было, но добавить его дважды нельзя
    const CriminalCase c(archive, "Д-9", 2021, "Описание", theft, smirnov.getId());
    archive.addCase(c);
    EXPECT_THROW(archive.addCase(c), std::invalid_argument);
    EXPECT_EQ(archive.getCases().size(), 4u);
    EXPECT_TRUE(archive.hasCase("Д-9"));
}

TEST_F(ArchiveTest, HasConvictAndInvestigator) {
    EXPECT_TRUE(archive.hasConvict(orlov.getId()));
    EXPECT_FALSE(archive.hasInvestigator(orlov.getId()));   // Орлов осужденный, а не следователь
    EXPECT_TRUE(archive.hasInvestigator(smirnov.getId()));
    EXPECT_FALSE(archive.hasConvict(smirnov.getId()));
    EXPECT_FALSE(archive.hasConvict(-1));
}

TEST_F(ArchiveTest, FindByIdReturnsReferenceToArchiveObject) {
    const Convict& c = archive.findConvictById(orlov.getId());
    EXPECT_EQ(c.getFullName(), "Орлов С. Н.");
    EXPECT_EQ(c.getSentence(), "5 лет");
    EXPECT_EQ(&c, &archive.getConvicts()[0]);   // ссылка на объект внутри архива, а не новая копия

    const Investigator& i = archive.findInvestigatorById(smirnov.getId());
    EXPECT_EQ(i.getRank(), "майор");
}

TEST_F(ArchiveTest, FindByIdThrowsIfNotFound) {
    EXPECT_THROW(archive.findConvictById(-1), std::out_of_range);
    EXPECT_THROW(archive.findInvestigatorById(orlov.getId()), std::out_of_range);
}

TEST_F(ArchiveTest, BaseTypeCollectionPolymorphism) {
    // Коллекция объектов базового типа, заполненная объектами наследников (как в main)
    const std::vector<std::reference_wrapper<const Person>> people = {
        std::cref(smirnov), std::cref(kuznetsova), std::cref(orlov), std::cref(volkov)
    };
    int convicts = 0;
    int investigators = 0;
    for (const Person& p : people) {
        if (dynamic_cast<const Convict*>(&p) != nullptr) {
            convicts++;
            EXPECT_NE(p.getInfo().find("Осужденный"), std::string::npos);
        }
        if (dynamic_cast<const Investigator*>(&p) != nullptr) {
            investigators++;
            EXPECT_NE(p.getInfo().find("Следователь"), std::string::npos);
        }
    }
    EXPECT_EQ(convicts, 2);
    EXPECT_EQ(investigators, 2);
}

TEST_F(ArchiveTest, FindByConvict) {
    const std::vector<CriminalCase> found = archive.findByConvict("Орлов С. Н.");
    ASSERT_EQ(found.size(), 2u);
    EXPECT_EQ(found[0].getNumber(), "Д-1");
    EXPECT_EQ(found[1].getNumber(), "Д-3");

    EXPECT_EQ(archive.findByConvict("Волков Д. А.").size(), 2u);
    EXPECT_TRUE(archive.findByConvict("Неизвестный").empty());
}

TEST_F(ArchiveTest, FindByConvictIgnoresInvestigators) {
    EXPECT_TRUE(archive.findByConvict("Смирнов А. П.").empty());
}

TEST_F(ArchiveTest, FindByInvestigator) {
    const std::vector<CriminalCase> found = archive.findByInvestigator("Смирнов А. П.");
    ASSERT_EQ(found.size(), 2u);
    EXPECT_EQ(found[0].getNumber(), "Д-1");
    EXPECT_EQ(found[1].getNumber(), "Д-3");

    EXPECT_EQ(archive.findByInvestigator("Кузнецова О. И.").size(), 1u);
    EXPECT_TRUE(archive.findByInvestigator("Орлов С. Н.").empty());
}

TEST_F(ArchiveTest, FindByContent) {
    EXPECT_EQ(archive.findByContent("магазин").size(), 2u);
    EXPECT_EQ(archive.findByContent("недвижимост").size(), 1u);
    EXPECT_TRUE(archive.findByContent("отсутствует").empty());
    EXPECT_TRUE(archive.findByContent("").empty());
}

TEST_F(ArchiveTest, FindByArticle) {
    EXPECT_EQ(archive.findByArticle("ст. 158").size(), 2u);
    EXPECT_EQ(archive.findByArticle("Мошенничество").size(), 1u);
    EXPECT_TRUE(archive.findByArticle("ст. 999").empty());
}

TEST_F(ArchiveTest, GetCaseInfoContainsNames) {
    const std::string info = archive.getCaseInfo(archive.getCases()[2]);
    EXPECT_NE(info.find("Д-3"), std::string::npos);
    EXPECT_NE(info.find("Смирнов А. П."), std::string::npos);
    EXPECT_NE(info.find("Орлов С. Н."), std::string::npos);
    EXPECT_NE(info.find("Волков Д. А."), std::string::npos);
}

TEST_F(ArchiveTest, GetCaseInfoUnknownPerson) {
    // дело создано в другом архиве, поэтому его следователя в нашем архиве нет
    Archive other;
    const Investigator stranger("Посторонний", "01.01.1980", "лейтенант");
    other.addInvestigator(stranger);
    const CriminalCase c(other, "Д-9", 2021, "Описание", Article(other, "ст. 1", "Тест"), stranger.getId());

    const std::string info = archive.getCaseInfo(c);
    EXPECT_NE(info.find("не найден"), std::string::npos);
}
