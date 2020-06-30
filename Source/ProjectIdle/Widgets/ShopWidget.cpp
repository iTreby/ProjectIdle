// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopWidget.h"
#include "ProjectIdle/GameManager.h"
#include "ProjectIdle/OfficeDepartment.h"
#include "ProjectIdle/CeoDepMenuWidget.h"
#include "ProjectIdle/WorldObject/Wall.h"
#include "ProjectIdle/Shop/ItemButton.h"
#include "ProjectIdle/Shop/Item.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UShopWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameManager = GetWorld()->GetGameInstance<UGameManager>();
	GameManager->ShopWidget = this;

	Money_T->SetText(FText::AsCurrency(GameManager->Money));

	if (!Buy_Btn->OnClicked.IsBound())
	{
		Buy_Btn->OnClicked.AddDynamic(this, &UShopWidget::Buy);
	}
	if (!EmptyCart_Btn->OnClicked.IsBound())
	{
		EmptyCart_Btn->OnClicked.AddDynamic(this, &UShopWidget::EmptyCart);
	}
	if (!ShopReturn_Btn->OnClicked.IsBound())
	{
		ShopReturn_Btn->OnClicked.AddDynamic(this, &UShopWidget::Return);
	}
}

void UShopWidget::Buy()
{
	if (GameManager->Money >= Total)
	{
		if (CheckList.Num() > 0)
		{
			/*for (int i = 0; i < CheckList.Num(); i++)
			{
				if (CheckList[i]->ItemCount > 1)
				{
					for (int j = 0; j < CheckList[i]->ItemCount; j++)
					{
						GameManager->InventoryList.Add(CheckList[i]->Item);

						GEngine->AddOnScreenDebugMessage(100, 5.f, FColor::Red, FString::FromInt(j + 1) + " " + CheckList[i]->Item->ItemName + "Added");
					}
				}
				else
				{
					if (CheckList[i]->Item->ItemCategory == ECategory::Materials)
					{
						for (int j = 0; j < GameManager->FloorList.Num(); j++)
						{
							GameManager->FloorList[j]->UpdateWallMaterial(CheckList[i]->Item->Material->GetMaterial());
							GEngine->AddOnScreenDebugMessage(100, 5.f, FColor::Red, "Noob");
						}

						for (int j = 0; j < Tab4->GetChildrenCount(); j++)
						{
							auto materialButton = Cast<UItemButton>(Tab4->GetChildAt(j));

							if (CheckList[i]->ItemID == materialButton->ItemID)
							{
								materialButton->Bought_T->SetText(FText::FromString("Bought"));
							}
						}

					}
					GameManager->InventoryList.Add(CheckList[i]->Item);

					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "1 " + CheckList[i]->Item->ItemName + "Added");
				}
			}*/
			
			for (int i = 0; i < CheckList.Num(); i++)
			{
				/*if (GameManager->InventoryList.Num() > 0)
				{
					for (int j = 0; j < GameManager->InventoryList.Num(); j++)
					{
						if (CheckList[i]->ItemID == GameManager->InventoryList[j]->ItemID)
						{
							GameManager->InventoryList[j]->ItemButton->ItemCount += CheckList[i]->ItemCount;
							break;
						}
						else
						{
							GameManager->InventoryList.Add(CheckList[i]->Item);
						}
					}
				}*/
				GameManager->InventoryList.Add(CheckList[i]->Item);

				if (CheckList[i]->Item->ItemCategory == ECategory::Materials || CheckList[i]->Item->ItemCategory == ECategory::OfficeDecorations)
				{
					GameManager->OfficeDepartment->OfficeDepMenuWidget->AddItemToInventory(CheckList[i]->Item);
				}

				if (CheckList[i]->Item->ItemCategory == ECategory::Materials)
				{
					for (int j = 0; j < Tab4->GetChildrenCount(); j++)
					{
						auto materialButton = Cast<UItemButton>(Tab4->GetChildAt(j));

						if (CheckList[i]->ItemID == materialButton->ItemID)
						{
							materialButton->Bought_T->SetText(FText::FromString("Bought"));
						}
					}
				}
			}

			GameManager->Money -= Total;
			Money_T->SetText(FText::AsCurrency(GameManager->Money));

			CheckoutItems_WB->ClearChildren();
			CheckList.Empty();

			Total = 0;
			CheckoutCount = 0;

			TotalMoney_T->SetText(FText::AsCurrency(Total));
			CheckoutCount_T->SetText(FText::FromString(FString::FromInt(CheckoutCount)));
		}
	}
	else
	{
		NotEnoughMoney_T->SetText(FText::FromString("Not enough money."));

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UShopWidget::RemoveNotEnoughMoney, 5.f, false);
	}
}

void UShopWidget::AddItemToCheckout(class AItem* item)
{
	bool isInCheckout = false;

	if (CheckList.Num() > 0)
	{
		for (size_t i = 0; i < CheckList.Num(); i++)
		{
			if (CheckList[i]->ItemID == item->ItemID)
			{
				CheckList[i]->ItemCount++;
				CheckList[i]->ItemCount_T->SetText(FText::FromString(FString::FromInt(CheckList[i]->ItemCount)));

				Total += CheckList[i]->Item->ItemPrice;
				TotalMoney_T->SetText(FText::AsCurrency(Total));

				isInCheckout = true;

				break;
			}
		}

		if (!isInCheckout)
		{
			auto ItemButton = CreateWidget<UItemButton>(this, ItemButtonClass);

			ItemButton->Item = item;
			ItemButton->BPItem = item->ItemButton->BPItem;

			ItemButton->ItemID = item->ItemID;

			ItemButton->InCheckout = true;

			Total += ItemButton->Item->ItemPrice;
			TotalMoney_T->SetText(FText::AsCurrency(Total));

			CheckList.Add(ItemButton);
			CheckoutItems_WB->AddChildToWrapBox(ItemButton);
		}
	}
	else
	{
		auto ItemButton = CreateWidget<UItemButton>(this, ItemButtonClass);

		ItemButton->BPItem = item->ItemButton->BPItem;
		ItemButton->Item = item;

		ItemButton->ItemID = item->ItemID;

		ItemButton->InCheckout = true;

		Total += ItemButton->Item->ItemPrice;
		TotalMoney_T->SetText(FText::AsCurrency(Total));

		CheckList.Add(ItemButton);
		CheckoutItems_WB->AddChildToWrapBox(ItemButton);
	}

	CheckoutCount++;
	CheckoutCount_T->SetText(FText::FromString(FString::FromInt(CheckoutCount)));
}

void UShopWidget::RemoveItemFromCheckout(int itemID)
{
	for (size_t i = 0; i < CheckList.Num(); i++)
	{
		if (CheckList[i]->ItemID == itemID)
		{
			if (CheckList[i]->ItemCount == 1)
			{
				CheckList[i]->ItemCount = 1;
				CheckList[i]->ItemCount_T->SetText(FText::FromString(" "));

				Total -= CheckList[i]->Item->ItemPrice;
				TotalMoney_T->SetText(FText::AsCurrency(Total));

				CheckoutItems_WB->RemoveChild(CheckList[i]);
				CheckList.RemoveAt(i);

				break;
			}
			else if (CheckList[i]->ItemCount > 1)
			{
				CheckList[i]->ItemCount--;
				CheckList[i]->ItemCount_T->SetText(FText::FromString(FString::FromInt(CheckList[i]->ItemCount)));

				if (CheckList[i]->ItemCount == 1)
				{
					CheckList[i]->ItemCount_T->SetText(FText::FromString(" "));
				}

				Total -= CheckList[i]->Item->ItemPrice;
				TotalMoney_T->SetText(FText::AsCurrency(Total));

				break;
			}
		}
	}

	CheckoutCount--;
	CheckoutCount_T->SetText(FText::FromString(FString::FromInt(CheckoutCount)));
}

void UShopWidget::EmptyCart()
{
	if (CheckList.Num() > 0)
	{
		for (size_t i = 0; i < CheckList.Num(); i++)
		{
			if (CheckList[i]->Item->ItemCategory == ECategory::Materials)
			{
				for (size_t j = 0; j < Tab4->GetChildrenCount(); j++)
				{
					auto materialButton = Cast<UItemButton>(Tab4->GetChildAt(j));

					if (CheckList[i]->ItemID == materialButton->ItemID)
					{
						materialButton->BoughtItem_I->SetVisibility(ESlateVisibility::Hidden);
						materialButton->Bought_T->SetVisibility(ESlateVisibility::Hidden);
					}
				}
			}
		}

		CheckoutItems_WB->ClearChildren();
		CheckList.Empty();

		Total = 0;
		CheckoutCount = 0;

		TotalMoney_T->SetText(FText::AsCurrency(Total));
		CheckoutCount_T->SetText(FText::FromString(FString::FromInt(CheckoutCount)));
	}
}

void UShopWidget::RemoveNotEnoughMoney()
{
	NotEnoughMoney_T->SetText(FText::FromString(""));
}

void UShopWidget::Return()
{
	CheckoutPanel->SetVisibility(ESlateVisibility::Hidden);
	OfficeDepartment->ShopReturn();
}
